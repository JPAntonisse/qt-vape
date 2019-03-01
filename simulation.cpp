#include "simulation.h"

#include "rfftw.h"
#include <QtCore/qmath.h>
#include <QDebug>
#include <QObject>


const int m_gridSize = 100;

Simulation::~Simulation()
{
}

Simulation::Simulation(DataController *datacontroller) :
    dataController(datacontroller)
{
//    qDebug() << "Constructor Simulation...";
    init(m_gridSize);
    // create a timer
    timer = new QTimer(this);

    // setup signal and slot
    connect(timer, SIGNAL(timeout()),
            this, SLOT(update()));

    timer->start(1000/30);
}

//void Simulation::update(SurfaceGraph *m_surfacegraph)
void Simulation::update()
{
//    if (!frozen)
//    {

    setForces();
    solve(m_gridSize, vx, vy, vx0, vy0, visc, dt);
    diffuseMatter(m_gridSize, vx, vy, rho, rho0, dt);
    visualize();

//        glutPostRedisplay();
//    }

    //TODO: Send update signal
//    qDebug() << "Update done...";
}

void Simulation::visualize()
{
    int i, j, idx;
    QSurfaceDataArray *dataArray = new QSurfaceDataArray;
    dataArray->reserve(m_gridSize);

    for (j = 0; j < m_gridSize; j++) {
        QSurfaceDataRow *newRow = new QSurfaceDataRow(m_gridSize);
        for (i = 0; i < m_gridSize; i++) {
            idx = (j * m_gridSize) + i;
            (*newRow)[i].setPosition(QVector3D(j, rho[idx], i));
        }
        *dataArray << newRow;
    }
    //Data controller -> setData
    dataController->setDataSurfaceGraph(dataArray);
    //m_surface->resetData(dataArray);
}

void Simulation::setForces()
{
    int i;
    for (i = 0; i < m_gridSize * m_gridSize; i++)
    {
        rho0[i]  = 0.995 * rho[i];
        fx[i] *= 0.95;
        fy[i] *= 0.95;
        vx0[i]    = fx[i];
        vy0[i]    = fy[i];
    }
}

void Simulation::init(int gridSize)
{
    int i; size_t dim;

    dim      = gridSize * 2 * (gridSize/2+1) * sizeof(fftw_real);//Allocate data structures
    vx       = static_cast<fftw_real*>(malloc(dim));
    vy       = static_cast<fftw_real*>(malloc(dim));
    vx0      = static_cast<fftw_real*>(malloc(dim));
    vy0      = static_cast<fftw_real*>(malloc(dim));

    dim     = gridSize * gridSize * sizeof(fftw_real);//Allocate data structures
    fx      = static_cast<fftw_real*>(malloc(dim));
    fy      = static_cast<fftw_real*>(malloc(dim));
    rho     = static_cast<fftw_real*>(malloc(dim));
    rho0    = static_cast<fftw_real*>(malloc(dim));

    plan_rc = rfftw2d_create_plan(gridSize, gridSize, FFTW_REAL_TO_COMPLEX, FFTW_IN_PLACE);
    plan_cr = rfftw2d_create_plan(gridSize, gridSize, FFTW_COMPLEX_TO_REAL, FFTW_IN_PLACE);

    for (i = 0; i < gridSize * gridSize; i++) //Initialize data structures to 0
    { vx[i] = vy[i] = vx0[i] = vy0[i] = fx[i] = fy[i] = rho[i] = rho0[i] = 0.0f; }
}

void Simulation::solve(int n, fftw_real* vx, fftw_real* vy, fftw_real* vx0, fftw_real* vy0, fftw_real visc, fftw_real dt)
{
    fftw_real x, y, x0, y0, f, r, U[2], V[2], s, t;
    int i, j, i0, j0, i1, j1;

    for (i=0; i<n*n; i++)
    { vx[i] += dt*vx0[i]; vx0[i] = vx[i]; vy[i] += dt*vy0[i]; vy0[i] = vy[i]; }

    for ( x=0.5f/n,i=0; i<n; i++,x+=1.0f/n )
        for ( y=0.5f/n,j=0; j<n; j++,y+=1.0f/n )
        {
            x0 = n*(x-dt*vx0[i+n*j])-0.5f;
            y0 = n*(y-dt*vy0[i+n*j])-0.5f;
            i0 = clamp(x0); s = x0-i0;
            i0 = (n+(i0%n))%n;
            i1 = (i0+1)%n;
            j0 = clamp(y0); t = y0-j0;
            j0 = (n+(j0%n))%n;
            j1 = (j0+1)%n;
            vx[i+n*j] = (1-s)*((1-t)*vx0[i0+n*j0]+t*vx0[i0+n*j1])+s*((1-t)*vx0[i1+n*j0]+t*vx0[i1+n*j1]);
            vy[i+n*j] = (1-s)*((1-t)*vy0[i0+n*j0]+t*vy0[i0+n*j1])+s*((1-t)*vy0[i1+n*j0]+t*vy0[i1+n*j1]);
        }

    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
        {  vx0[i+(n+2)*j] = vx[i+n*j]; vy0[i+(n+2)*j] = vy[i+n*j]; }

    fft(1,vx0);
    fft(1,vy0);

    for (i=0; i<=n; i+=2)
    {
        x = 0.5f*i;
        for (j=0; j<n; j++)
        {
            y = j<=n/2 ? (fftw_real)j : (fftw_real)j-n;
            r = x*x+y*y;
            if ( r==0.0f ) continue;
            f = (fftw_real)exp(-r*dt*visc);
            U[0] = vx0[i  +(n+2)*j]; V[0] = vy0[i  +(n+2)*j];
            U[1] = vx0[i+1+(n+2)*j]; V[1] = vy0[i+1+(n+2)*j];

            vx0[i  +(n+2)*j] = f*((1-x*x/r)*U[0]     -x*y/r *V[0]);
            vx0[i+1+(n+2)*j] = f*((1-x*x/r)*U[1]     -x*y/r *V[1]);
            vy0[i+  (n+2)*j] = f*(  -y*x/r *U[0] + (1-y*y/r)*V[0]);
            vy0[i+1+(n+2)*j] = f*(  -y*x/r *U[1] + (1-y*y/r)*V[1]);
        }
    }

    fft(-1,vx0);
    fft(-1,vy0);

    f = 1.0/(n*n);
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
        { vx[i+n*j] = f*vx0[i+(n+2)*j]; vy[i+n*j] = f*vy0[i+(n+2)*j]; }
}

void Simulation::diffuseMatter(int n, fftw_real *vx, fftw_real *vy, fftw_real *rho, fftw_real *rho0, fftw_real dt)
{
    fftw_real x, y, x0, y0, s, t;
    int i, j, i0, j0, i1, j1;

    for ( x=0.5f/n,i=0; i<n; i++,x+=1.0f/n )
        for ( y=0.5f/n,j=0; j<n; j++,y+=1.0f/n )
        {
            x0 = n*(x-dt*vx[i+n*j])-0.5f;
            y0 = n*(y-dt*vy[i+n*j])-0.5f;
            i0 = clamp(x0);
            s = x0-i0;
            i0 = (n+(i0%n))%n;
            i1 = (i0+1)%n;
            j0 = clamp(y0);
            t = y0-j0;
            j0 = (n+(j0%n))%n;
            j1 = (j0+1)%n;
            rho[i+n*j] = (1-s)*((1-t)*rho0[i0+n*j0]+t*rho0[i0+n*j1])+s*((1-t)*rho0[i1+n*j0]+t*rho0[i1+n*j1]);
        }
}

void Simulation::drag(int X, int Y, float dx, float dy)
{
    int around = 3;

    fx[X * m_gridSize + Y] += dy;
    fy[X * m_gridSize + Y] += dx;
    rho[X * m_gridSize + Y] = 1.0f;

    int x, y;


    for(x = -around; x < around; x++) {
        for(y = -around; y < around; y++) {
            int xRC = rotateClamp(x + X, 0, m_gridSize);
            int yRC = rotateClamp(y + Y, 0, m_gridSize);
            rho[xRC * m_gridSize + yRC] = 0.3f - 0.3f * sqrt(pow(abs(x), 2) + pow(abs(y), 2))/pow(around, 2);
        }
    }
}

int Simulation::clamp(float x)
{
    return (static_cast<double>(x)>=0.0 ? (static_cast<int>(x)) : (-(static_cast<int>(1-(x)))));
}

int Simulation::rotateClamp(int x, int min, int max)
{
    if(x < min)
        return max - (min - x);
    else if(x > max)
        return (x - max) + min;
    else
        return x;
}

void Simulation::fft(int direction, void* vx)
{
    if(direction==1)
        rfftwnd_one_real_to_complex(plan_rc, static_cast<fftw_real*>(vx), static_cast<fftw_complex*>(vx));
    else
        rfftwnd_one_complex_to_real(plan_cr,static_cast<fftw_complex*>(vx), static_cast<fftw_real*>(vx));
}

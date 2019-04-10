#include "simulation.h"

#include "rfftw.h"
#include <QtCore/qmath.h>
#include <QtDataVisualization/QCustom3DItem>
#include <QDebug>
#include <QObject>
#include <cmath>


const int m_gridSize = 100;
const double m_gridSize_double = 100.0;
const double pi = 3.14159265358979323846;
static const float verticalRange = 8.0f;
static const float horizontalRange = verticalRange;
static const float ellipse_a = horizontalRange / 3.0f;
static const float ellipse_b = verticalRange;
static const float doublePi = float(M_PI) * 2.0f;
static const float radiansToDegrees = 360.0f / doublePi;
static const float animationFrames = 30.0f;
static const double gridSize = 100.0;

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

    //dataController->

    // setup signal and slot
    connect(timer, SIGNAL(timeout()),
            this, SLOT(update()));

    timer->start(1000/30);
}

//void Simulation::update(SurfaceGraph *m_surfacegraph)
void Simulation::update()
{
    if (pause)
        return;

    setForces();

    solve(m_gridSize, vx, vy, vx0, vy0, visc, dt);
    diffuseMatter(m_gridSize, vx, vy, rho, rho0, dt);

    setDivergence();

//    if(type) visualizeQSurface();
//    else visualizeQScatter();

    visualize();
}

int Simulation::getGridSize(){
    return m_gridSize;
}

void Simulation::visualize(){
    if (visualizationType){
        visualizeQSurface();
    } else {
        visualizeQScatter();
        visualizeQSurface();
    }
}

void Simulation::setVisualizationType(bool set){
    visualizationType = set;
}

void Simulation::visualizeQSurface()
{
    int i, j, idx;
    QSurfaceDataArray *dataArray = new QSurfaceDataArray;
    dataArray->reserve(m_gridSize);

    for (j = 0; j < m_gridSize; j++) {
        QSurfaceDataRow *newRow = new QSurfaceDataRow(m_gridSize);
        for (i = 0; i < m_gridSize; i++) {
            idx = (j * m_gridSize) + i;
            (*newRow)[i].setPosition(QVector3D(j, getDataPoint(idx), i));
        }
        *dataArray << newRow;
    }
    //Data controller -> setData
    dataController->setDataSurfaceGraph(dataArray);
    //m_surface->resetData(dataArray);
}

void Simulation::setColorMap(QString type){
    colorMapType = type;
}

void Simulation::visualizeQScatter(){
    QVector<QCustom3DItem*> m_arrows = dataController->getSurfaceGraph()->getArrows();
    int i, j, idx;
    if(uniformGrid){
        for (j = 0; j < m_gridSize; j++) {

            for (i = 0; i < m_gridSize; i++) {

                idx = (i * m_gridSize) + j;
                QQuaternion rotation = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, getRotationArrow(idx, m_arrows.at(idx)));
                m_arrows.at(idx)->setRotation(rotation);
            }
        }
    }else{
        for (j = 0; j < m_arrows.size(); j++) {
                QQuaternion rotation = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, getRotationArrow(j, m_arrows.at(j)));
                m_arrows.at(j)->setRotation(rotation);
        }
    }

    //Data controller -> setData
    //dataController->getScatterGraph()->resetData(m_magneticFieldArray);
}
void Simulation::setGridType(bool type){
    uniformGrid = type;
}

void Simulation::setArrowScale(double scale){
    arrowScale = scale;
}


void Simulation::setArrowSize(fftw_real force, QCustom3DItem* arrow){
    double realForce = abs(force);
    if(realForce > (0.04)){
        arrow->setScaling(QVector3D((0.04 * arrowScale), (0.04 * arrowScale), (0.04 * arrowScale)));
    }else if (realForce < (0.02)){
        arrow->setScaling(QVector3D((0.02 * arrowScale), (0.02 * arrowScale), (0.02 * arrowScale)));
    }else{
        arrow->setScaling(QVector3D((0.03 * arrowScale), (0.03 * arrowScale), (0.03 * arrowScale)));
    }
}

void Simulation::setArrowColor(fftw_real force, QCustom3DItem* arrow){
    QImage color = QImage(1, 1, QImage::Format_A2BGR30_Premultiplied);
    QColor colord;
    double realForce = abs(force);
    if(colorMapType == 'greenred'){
        if(realForce > 0.04){
            colord = QColor(255, 0, 0);
        }else if (realForce < 0.01){
            //int a = floor((255/0.04)*(realForce-0.01));
            //qDebug() << a;
            //
            colord = QColor(124, 124, 0);
        }else{
            colord = QColor(0, 255, 0);
        }
    }
    color.fill(colord);

    arrow->setTextureImage(color);

}

void Simulation::recolorToStandard(){
    QVector<QCustom3DItem*> m_arrows = dataController->getSurfaceGraph()->getArrows();
    QImage color = QImage(1, 1, QImage::Format_A2BGR30_Premultiplied);
    color.fill(Qt::green);
    for (int j = 0; j < m_arrows.size(); j++) {
            m_arrows.at(j)->setTextureImage(color);
    }
}

bool Simulation::isUniformGrid(){
    return uniformGrid;
}

void Simulation::setUniformGrid(bool set){
    uniformGrid = set;
}

fftw_real Simulation::getDataPoint(int idx)
{
    if(visualize_data == Simulation::DENSITY) {
        return rho[idx];
    } else if (visualize_data == Simulation::VELOCITY) {
        return sqrt(pow(vx[idx], 2) + pow(vy[idx], 2)) * 20;
    } else if (visualize_data == Simulation::FORCE) {
        return sqrt(pow(fx[idx], 2) + pow(fy[idx], 2));
    } else if (visualize_data == Simulation::DIVERGENCE) {
        return sqrt(pow(divx[idx], 2) + pow(divy[idx], 2)) * 40;
    }

    return rho[idx];
}

float Simulation::getRotationArrow(int idx, QCustom3DItem* arrow){
    if(!uniformGrid){
        fftw_real ix, iy = 0;
        ix = interpolate(arrow, true);
        iy = interpolate(arrow, false);
        setArrowSize(ix + iy, arrow);
        if(colorMapActive){
            setArrowColor(ix + iy, arrow);
        }
        return atan2(-iy, ix)*(180.0/pi);
    }else{
        if (visualize_data == Simulation::VELOCITY) {
            setArrowSize(vy[idx] + vx[idx], arrow);
            if(colorMapActive){
                setArrowColor(vy[idx] + vx[idx], arrow);
            }
            return atan2(-vy[idx], vx[idx])*(180.0/pi);
        } else if (visualize_data == Simulation::FORCE) {
            setArrowSize(fy[idx] + fx[idx], arrow);
            if(colorMapActive){
                setArrowColor(fy[idx] + fx[idx], arrow);
            }
            return atan2(-fy[idx], fx[idx])*(180.0/pi);
        }
    }
}

void Simulation::setGlyphColorActive(bool set){
    colorMapActive = set;
}

double Simulation::interpolate(QCustom3DItem* arrow, bool direction){
    int x = floor(arrow->position().x());
    double xdiff = arrow->position().x() - floor(arrow->position().x());
    int z = floor(arrow->position().z());
    double zdiff = arrow->position().z() - floor(arrow->position().x());

    double sum = 0;
    if (visualize_data == Simulation::VELOCITY) {
        if(direction){
            double E = (vx[(x * m_gridSize) + z] + xdiff * (vx[((x+1) * m_gridSize) + z] - vx[(x * m_gridSize) + z]));
            double F = (vx[(x * m_gridSize) + z+1] + xdiff * (vx[((x+1) * m_gridSize) + z+1] - vx[(x * m_gridSize) + z+1]));
            sum =  E + zdiff * (F-E);
        }else{
            double E = (vy[(x * m_gridSize) + z] + xdiff * (vy[((x+1) * m_gridSize) + z] - vy[(x * m_gridSize) + z]));
            double F = (vy[(x * m_gridSize) + z+1] + xdiff * (vy[((x+1) * m_gridSize) + z+1] - vy[(x * m_gridSize) + z+1]));
            sum =  E + zdiff * (F-E);
        }
    }else if (visualize_data == Simulation::FORCE) {
        if(direction){
            double E = (fx[(x * m_gridSize) + z] + xdiff * (fx[((x+1) * m_gridSize) + z] - fx[(x * m_gridSize) + z]));
            double F = (fx[(x * m_gridSize) + z+1] + xdiff * (fx[((x+1) * m_gridSize) + z+1] - fx[(x * m_gridSize) + z+1]));
            sum =  E + zdiff * (F-E);
        }else{
            double E = (fy[(x * m_gridSize) + z] + xdiff * (fy[((x+1) * m_gridSize) + z] - fy[(x * m_gridSize) + z]));
            double F = (fy[(x * m_gridSize) + z+1] + xdiff * (fy[((x+1) * m_gridSize) + z+1] - fy[(x * m_gridSize) + z+1]));
            sum =  E + zdiff * (F-E);
        }
    }
    return sum;
}

void Simulation::setDataSet(QString dataSet)
{
    if(dataSet == (QString) "density") {
        visualize_data = Simulation::DENSITY;
    } else if (dataSet == (QString) "velocity") {
        visualize_data = Simulation::VELOCITY;
    } else if (dataSet == (QString) "force") {
        visualize_data = Simulation::FORCE;
    } else if (dataSet == (QString) "divergence") {
        visualize_data = Simulation::DIVERGENCE;
    }
    if (pause) {
        visualize();
    }
}


void Simulation::pauseSimulation(bool i_pause)
{
    pause = i_pause;
}


//void Simulation::getData()
//{
//    switch(this->m_dataset) {
//       case constant-expression  :
//          statement(s);
//          break; //optional
//       case constant-expression  :
//          statement(s);
//          break; //optional

//       // you can have any number of case statements.
//       default : //Optional
//          statement(s);
//    }
//}

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
        vvx0[i]    = vx[i];
        vvy0[i]    = vy[i];

    }
}
void Simulation::setDivergence()
{
    int i;
    for (i = 0; i < m_gridSize * m_gridSize; i++)
    {
        divx[i]   = vvx0[i] - vx[i];
        divy[i]   = vvy0[i] - vy[i];
    }
}

void Simulation::init(int gridSize)
{
    int i; size_t dim;

    dim      = gridSize * 2 * (gridSize/2+1) * sizeof(fftw_real);//Allocate data structures
    vx       = static_cast<fftw_real*>(malloc(dim));
    vy       = static_cast<fftw_real*>(malloc(dim));
    divx     = static_cast<fftw_real*>(malloc(dim));
    divy     = static_cast<fftw_real*>(malloc(dim));
    vx0      = static_cast<fftw_real*>(malloc(dim));
    vy0      = static_cast<fftw_real*>(malloc(dim));
    vvx0      = static_cast<fftw_real*>(malloc(dim));
    vvy0      = static_cast<fftw_real*>(malloc(dim));

    dim     = gridSize * gridSize * sizeof(fftw_real);//Allocate data structures
    fx      = static_cast<fftw_real*>(malloc(dim));
    fy      = static_cast<fftw_real*>(malloc(dim));
    rho     = static_cast<fftw_real*>(malloc(dim));
    rho0    = static_cast<fftw_real*>(malloc(dim));

    plan_rc = rfftw2d_create_plan(gridSize, gridSize, FFTW_REAL_TO_COMPLEX, FFTW_IN_PLACE);
    plan_cr = rfftw2d_create_plan(gridSize, gridSize, FFTW_COMPLEX_TO_REAL, FFTW_IN_PLACE);

    for (i = 0; i < gridSize * gridSize; i++) //Initialize data structures to 0
    { vx[i] = vy[i] = vx0[i] = vy0[i] = vvx0[i] = vvy0[i] = fx[i] = fy[i] = rho[i] = rho0[i] = divx[i] = divy[i] = 0.0f; }


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
            rho[xRC * m_gridSize + yRC] = 10.0f - 10.0f * sqrt(pow(abs(x), 2) + pow(abs(y), 2))/pow(around, 2);
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

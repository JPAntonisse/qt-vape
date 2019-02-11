#ifndef SIMULATION_H
#define SIMULATION_H

#include "rfftw.h"
#include "surfacegraph.h"
#include <QTimer>

class Simulation : public QObject
{

    Q_OBJECT

    public:
        explicit Simulation(SurfaceGraph *surfaceGraph);
        ~Simulation();

        QTimer *timer;

        void drag(int X, int Y, float dx, float dy);

    public slots:
        void update();

    private:
        float dt = 0.4;                                 //simulation time step
        float visc = 0.001;                             //fluid viscosity
        fftw_real *vx, *vy;                             //(vx,vy)   = velocity field at the current moment
        fftw_real *vx0, *vy0;                           //(vx0,vy0) = velocity field at the previous moment
        fftw_real *fx, *fy;                             //(fx,fy)   = user-controlled simulation forces, steered with the mouse
        fftw_real *rho, *rho0;                          //smoke density at the current (rho) and previous (rho0) moment
        rfftwnd_plan plan_rc, plan_cr;                  //simulation domain discretization

        SurfaceGraph *m_surface;

    private:
        void setForces();
        void visualize();

        void init(int gridSize);
        void fft(int direction,void* vx);
        void solve(int n, fftw_real* vx, fftw_real* vy, fftw_real* vx0, fftw_real* vy0, fftw_real visc, fftw_real dt);
        void diffuseMatter(int n, fftw_real *vx, fftw_real *vy, fftw_real *rho, fftw_real *rho0, fftw_real dt);

        int clamp(float x);
        int rotateClamp(int x, int min, int max);
};

#endif

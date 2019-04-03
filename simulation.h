#ifndef SIMULATION_H
#define SIMULATION_H

#include "rfftw.h"
#include "surfacegraph.h"
#include "datacontroller.h"
#include <QTimer>

class Simulation : public QObject
{

    Q_OBJECT

    public:
        explicit Simulation(DataController *dataController);
        ~Simulation();

        QTimer *timer;
        int DENSITY = 1;
        int VELOCITY = 2;
        int FORCE = 3;
        int DIVERGENCE = 4;
        void drag(int X, int Y, float dx, float dy);

    public slots:
        void update();
        void setDataSet(QString dataSet);
        void pauseSimulation(bool i_pause);
        void visualize();
        void setVisualizationType(bool set);
        void setArrowSize(fftw_real force, QCustom3DItem* arrow);
        void setArrowColor(fftw_real force, QCustom3DItem* arrow);
        float getRotationArrow(int idx, QCustom3DItem* arrow);
        double interpolate(QCustom3DItem* arrow, bool direction);
        void setGridType(bool type);
        bool isUniformGrid();
        void setUniformGrid(bool set);
        int getGridSize();
        void setColorMap(QString type);
        void setGlyphColorActive(bool set);
        void recolorToStandard();
        void setArrowScale(double scale);
    private:
        int visualize_data = Simulation::DENSITY;
        float dt = 0.4;                                 //simulation time step
        float visc = 0.001;                             //fluid viscosity
        fftw_real *vx, *vy;                             //(vx,vy)   = velocity field at the current moment
        fftw_real *vx0, *vy0;                           //(vx0,vy0) = velocity field at the previous moment
        fftw_real *fx, *fy;                             //(fx,fy)   = user-controlled simulation forces, steered with the mouse
        fftw_real *rho, *rho0;                          //smoke density at the current (rho) and previous (rho0) moment
        fftw_real *divx, *divy;                                 //divergence
        fftw_real *vvx0, *vvy0;                                 //divergence
        rfftwnd_plan plan_rc, plan_cr;                  //simulation domain discretization
        DataController *dataController;
        bool visualizationType = true;
        bool uniformGrid = true;
        bool pause = false;
        fftw_real getDataPoint(int idx);
        QString m_dataset;

        SurfaceGraph *m_surface;
        bool colorMapActive = false;
    private:
        void setForces();
        void setDivergence();
        void visualizeQSurface();
        void visualizeQScatter();

        void init(int gridSize);
        void fft(int direction,void* vx);
        void solve(int n, fftw_real* vx, fftw_real* vy, fftw_real* vx0, fftw_real* vy0, fftw_real visc, fftw_real dt);
        void diffuseMatter(int n, fftw_real *vx, fftw_real *vy, fftw_real *rho, fftw_real *rho0, fftw_real dt);

        QString colorMapType = QString('greenred');
        int clamp(float x);
        double arrowScale = 1.0;
        int rotateClamp(int x, int min, int max);
};

#endif

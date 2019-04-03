#ifndef CONTAINER_MANAGER_H
#define CONTAINER_MANAGER_H

#include "inputhandler.h"
#include "simulation.h"

#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QHeightMapSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>
#include <QtWidgets/QSlider>

using namespace QtDataVisualization;

class ContainerManager : public QObject
{
    Q_OBJECT
    public:
        explicit ContainerManager(QWidget *container_surface, Simulation *simulation, SurfaceGraph *surfaceGraph);
        ~ContainerManager();


    public Q_SLOTS:
        void showSurface(bool set);
        void setGridType(QString type);
        void setRandomGridAmountOfArrows(int amount);
        void addRandomGridArrows(int amount);
        void setBlackToYellowGradient();
        void setGreenToRedGradient();
        void setGlypColor(bool value);
    private:
        QWidget *m_surface;
        QWidget *m_scatter;
        SurfaceGraph *m_surfaceGraph;
        Simulation *m_simulation;

};

#endif

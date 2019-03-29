#include "container_manager.h"
#include "inputhandler.h"
#include "simulation.h"

#include <QtDataVisualization/QValue3DAxis>
#include <QtDataVisualization/Q3DTheme>
#include <QtGui/QImage>
#include <QtCore/qmath.h>

using namespace QtDataVisualization;

ContainerManager::ContainerManager(QWidget *container_surface, Simulation *simulation, SurfaceGraph *surfaceGraph):
    m_surface(container_surface),
    m_simulation(simulation),
    m_surfaceGraph(surfaceGraph)
{

}

ContainerManager::~ContainerManager()
{

}

void ContainerManager::showSurface(bool set)
{

    qDebug() << "TYPESET: " << set;
    if(set){
        m_simulation->setVisualizationType(true);
    }else{
        m_surfaceGraph->generateData();
        m_simulation->setVisualizationType(false);
    }

}


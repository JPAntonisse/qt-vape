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
    qDebug() << "ShowSurface";
    if(!set){
        m_simulation->setVisualizationType(true);
        m_surfaceGraph->clearData();
    }else{
        m_simulation->setGridType(true);
        m_surfaceGraph->generateData();
        m_simulation->setVisualizationType(false);
    }

}

void ContainerManager::setGridType(QString type)
{

    if(type == "uniform"){
        qDebug() << "Uniform";
        m_simulation->setUniformGrid(true);
        m_surfaceGraph->clearData();
        m_surfaceGraph->generateData();

    }else if(type == "random"){
        qDebug() << "Random";
        m_simulation->setUniformGrid(false);
        m_surfaceGraph->clearData();
        m_surfaceGraph->generateRandomGridData();
    }

}



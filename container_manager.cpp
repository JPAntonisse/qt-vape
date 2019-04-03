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
        m_simulation->setDataSet(QString("velocity"));
    }else{
        m_simulation->setGridType(true);
        m_surfaceGraph->generateData();
        m_simulation->setVisualizationType(false);
        m_simulation->setDataSet(QString("velocity"));
    }

}

void ContainerManager::setGridType(QString type)
{

    if(type == "uniform" && !m_simulation->isUniformGrid()){
        qDebug() << "Uniform";
        m_simulation->setUniformGrid(true);
        m_surfaceGraph->clearData();
        m_surfaceGraph->generateData();

    }else if(type == "random" && m_simulation->isUniformGrid()){
        qDebug() << "Random";
        m_simulation->setUniformGrid(false);
        m_surfaceGraph->clearData();
        m_surfaceGraph->generateRandomGridData(pow(m_simulation->getGridSize(), 2));
    }

}

void ContainerManager::setRandomGridAmountOfArrows(int amount){
    m_surfaceGraph->clearData();
    m_surfaceGraph->generateRandomGridData(amount);
}

void ContainerManager::setRandomArrows(double amount){
    qDebug() << "Add Random arrows: " << amount;
    m_surfaceGraph->clearData();
    m_surfaceGraph->generateRandomGridData(amount);
}

void ContainerManager::setBlackToYellowGradient(){
    m_surfaceGraph->setBlackToYellowGradient();
    m_simulation->setColorMap(QString('blackyellow'));
}

void ContainerManager::setGreenToRedGradient(){
    m_surfaceGraph->setGreenToRedGradient();
    m_simulation->setColorMap(QString('greenred'));
}

void ContainerManager::heightGlyphs(double height){
    m_surfaceGraph->setHeightArrows(height);
}

void ContainerManager::setGlypColor(bool value){
    qDebug() << " value: " << value;
    m_simulation->setGlyphColorActive(value);
    m_simulation->setColorMap(QString('greenred'));

    if(value == false){
        m_simulation->recolorToStandard();
    }
}



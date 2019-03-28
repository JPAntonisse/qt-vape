#include "container_manager.h"
#include "inputhandler.h"
#include "simulation.h"

#include <QtDataVisualization/QValue3DAxis>
#include <QtDataVisualization/Q3DTheme>
#include <QtGui/QImage>
#include <QtCore/qmath.h>

using namespace QtDataVisualization;

ContainerManager::ContainerManager(QWidget *container_surface, QWidget *container_scatter):
    m_surface(container_surface),
    m_scatter(container_scatter)
{

}

ContainerManager::~ContainerManager()
{

}

void ContainerManager::showSurface(bool show)
{
    qDebug() << "show : " << show;
    if (show) {
        m_scatter->hide();
        m_surface->show();
    } else {
        m_surface->hide();
        m_scatter->show();
    }
}


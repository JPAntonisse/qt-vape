#ifndef CONTAINER_MANAGER_H
#define CONTAINER_MANAGER_H

#include "inputhandler.h"

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
        explicit ContainerManager(QWidget *container_surface, QWidget *container_scatter);
        ~ContainerManager();


    public Q_SLOTS:
        void showSurface(bool);

    private:
        QWidget *m_surface;
        QWidget *m_scatter;

};

#endif

#include "surfacegraph.h"
#include "simulation.h"
#include "datacontroller.h"
#include "container_manager.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QtGui/QPainter>
#include <QtGui/QScreen>
#include <QtQuickWidgets/QQuickWidget>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QtQuick>


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Q3DSurface *graph = new Q3DSurface();
    Q3DScatter *q3dScatter = new Q3DScatter();

    QWidget *container_scatter = QWidget::createWindowContainer(q3dScatter);
    QWidget *container_surface = QWidget::createWindowContainer(graph);
    container_scatter->hide();

    InputHandler *inputhandler_scatter = new InputHandler(q3dScatter);
    InputHandler *inputhandler_surface = new InputHandler(graph);

    SurfaceGraph *surfaceGraph = new SurfaceGraph(graph, inputhandler_surface);
    ScatterGraph *scatterGraph = new ScatterGraph(q3dScatter, inputhandler_scatter);

    DataController *dataController = new DataController(surfaceGraph, scatterGraph);

    Simulation *simulation = new Simulation(dataController);

    QSize screenSize = graph->screen()->size();
    container_scatter->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.6));
    container_scatter->setMaximumSize(screenSize);
    container_surface->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.6));
    container_surface->setMaximumSize(screenSize);

    QWidget *widget = new QWidget;
    widget->setWindowTitle(QStringLiteral("Surface example"));
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    hLayout->setSpacing(0);
    hLayout->setMargin(0);

    QQuickStyle::setStyle("Material");
    QQuickWidget *m_quickWidget = new QQuickWidget;
    m_quickWidget->resize(400, 800);
    m_quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView );

    m_quickWidget->setSource(QUrl("qrc:/ControlPanel.qml"));
    QObject *item = m_quickWidget->rootObject();

    hLayout->addWidget(container_scatter, 1);
    hLayout->addWidget(container_surface, 1);
    hLayout->addWidget(m_quickWidget, 0);

    ContainerManager *container_m = new ContainerManager(container_surface, container_scatter);

    QObject::connect(inputhandler_scatter, &InputHandler::dragged,
                     simulation, &Simulation::drag);

    QObject::connect(inputhandler_surface, &InputHandler::dragged,
                     simulation, &Simulation::drag);

    QObject::connect(item, SIGNAL(setBlackToYellowGradient()),
                     surfaceGraph, SLOT(setBlackToYellowGradient()));

    QObject::connect(item, SIGNAL(setGreenToRedGradient()),
                     surfaceGraph, SLOT(setGreenToRedGradient()));

    QObject::connect(item, SIGNAL(drawWireFrame(bool)),
                     surfaceGraph, SLOT(drawWireFrame(bool)));

    QObject::connect(item, SIGNAL(showSurface(bool)),
                     container_m, SLOT(showSurface(bool)));

    QObject::connect(item, SIGNAL(setDataSet(QString)),
                     simulation, SLOT(setDataSet(QString)));

    QObject::connect(item, SIGNAL(hueRotation(double)),
                     surfaceGraph, SLOT(hueRotation(double)));


    widget->show();


    return app.exec();
}

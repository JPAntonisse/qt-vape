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
    QWidget *container_surface = QWidget::createWindowContainer(graph);

    InputHandler *inputhandler_surface = new InputHandler(graph);
    SurfaceGraph *surfaceGraph = new SurfaceGraph(graph, inputhandler_surface);
    DataController *dataController = new DataController(surfaceGraph);
    Simulation *simulation = new Simulation(dataController);

    QSize screenSize = graph->screen()->size();

    container_surface->setMinimumSize(QSize(screenSize.width() * 0.8, screenSize.height()));
    container_surface->setMaximumSize(screenSize);
    container_surface->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container_surface->setFocusPolicy(Qt::StrongFocus);

    QWidget *widget = new QWidget;
    widget->setWindowTitle(QStringLiteral("QT Vape"));

    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    hLayout->setSpacing(0);
    hLayout->setMargin(0);

    QQuickStyle::setStyle("Material");
    QQuickWidget *m_quickWidget = new QQuickWidget;
    m_quickWidget->setMinimumSize(QSize(screenSize.width() * 0.2, screenSize.height()));
    m_quickWidget->setMaximumSize(screenSize);
    m_quickWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_quickWidget->setFocusPolicy(Qt::StrongFocus);
    m_quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

    m_quickWidget->setSource(QUrl("qrc:/ControlPanel.qml"));
    QObject *item = m_quickWidget->rootObject();

    hLayout->addWidget(container_surface, 1);
    hLayout->addWidget(m_quickWidget);

    ContainerManager *container_m = new ContainerManager(container_surface, simulation, surfaceGraph);


    // SIMULATION
    QObject::connect(inputhandler_surface, &InputHandler::dragged,
                     simulation, &Simulation::drag);

    QObject::connect(item, SIGNAL(setDataSet(QString)),
                     simulation, SLOT(setDataSet(QString)));

    QObject::connect(item, SIGNAL(pauseSimulation(bool)),
                     simulation, SLOT(pauseSimulation(bool)));


    // CONTAINER

    QObject::connect(item, SIGNAL(setGridType(QString)),
                     container_m, SLOT(setGridType(QString)));


    QObject::connect(item, SIGNAL(showSurface(bool)),
                    container_m, SLOT(showSurface(bool)));

    QObject::connect(item, SIGNAL(setRandomArrows(double)),
                    container_m, SLOT(setRandomArrows(double)));

    QObject::connect(item, SIGNAL(heightGlyphs(double)),
                    container_m, SLOT(heightGlyphs(double)));

    QObject::connect(item, SIGNAL(setArrowSize(double)),
                    container_m, SLOT(setArrowSize(double)));


    // SURFACEGRAPH
    QObject::connect(item, SIGNAL(setIsoLineGradient()),
                     surfaceGraph, SLOT(setIsoLineGradient()));

    // SURFACEGRAPH
    QObject::connect(item, SIGNAL(setCustomIsoLineGradient()),
                     surfaceGraph, SLOT(setCustomIsoLineGradient()));


    QObject::connect(item, SIGNAL(setCustomIsolineMax(double)),
                     surfaceGraph, SLOT(setCustomIsolineMax(double)));

    QObject::connect(item, SIGNAL(setCustomIsolineMin(double)),
                     surfaceGraph, SLOT(setCustomIsolineMin(double)));

    QObject::connect(item, SIGNAL(setCustomIsolineInterval(int)),
                     surfaceGraph, SLOT(setCustomIsolineInterval(int)));


    QObject::connect(item, SIGNAL(setBlackToYellowGradient()),
                     surfaceGraph, SLOT(setBlackToYellowGradient()));


    QObject::connect(item, SIGNAL(setGreenToRedGradient()),
                     surfaceGraph, SLOT(setGreenToRedGradient()));

    QObject::connect(item, SIGNAL(drawWireFrame(bool)),
                     surfaceGraph, SLOT(drawWireFrame(bool)));

    QObject::connect(item, SIGNAL(setGlypColor(bool)),
                     container_m, SLOT(setGlypColor(bool)));

    QObject::connect(item, SIGNAL(hueRotation(double)),
                     surfaceGraph, SLOT(hueRotation(double)));

    QObject::connect(item, SIGNAL(isolineRotation(double)),
                     surfaceGraph, SLOT(isolineRotation(double)));

    QObject::connect(item, SIGNAL(scaleGraph(double)),
                     surfaceGraph, SLOT(scaleGraph(double)));

    QObject::connect(item, SIGNAL(enableFlatShading(bool)),
                     surfaceGraph, SLOT(enableFlatShading(bool)));

//    widget->showFullScreen();

    graph->show();
    widget->showMaximized();


    return app.exec();
}

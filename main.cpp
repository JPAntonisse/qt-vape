#include "surfacegraph.h"
#include "simulation.h"

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
    InputHandler *inputhandler = new InputHandler(graph);
    SurfaceGraph *surfaceGraph = new SurfaceGraph(graph, inputhandler);
    Simulation *simulation = new Simulation(surfaceGraph);


    QWidget *container = QWidget::createWindowContainer(graph);
    QSize screenSize = graph->screen()->size();
    container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.6));
    container->setMaximumSize(screenSize);

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

    hLayout->addWidget(container, 1);
    hLayout->addWidget(m_quickWidget, 0);

    QObject::connect(inputhandler, &InputHandler::dragged,
                     simulation, &Simulation::drag);

    QObject::connect(item, SIGNAL(setBlackToYellowGradient()),
                     surfaceGraph, SLOT(setBlackToYellowGradient()));

    QObject::connect(item, SIGNAL(setGreenToRedGradient()),
                     surfaceGraph, SLOT(setGreenToRedGradient()));

    QObject::connect(item, SIGNAL(drawWireFrame(bool)),
                     surfaceGraph, SLOT(drawWireFrame(bool)));

    QObject::connect(item, SIGNAL(setDataSet(QString)),
                     simulation, SLOT(setDataSet(QString)));

    widget->show();


    return app.exec();
}

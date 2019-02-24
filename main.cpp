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

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    Q3DSurface *graph = new Q3DSurface();
    InputHandler *inputhandler = new InputHandler(graph);

    SurfaceGraph *surfaceGraph = new SurfaceGraph(graph, inputhandler);
    Simulation *simulation = new Simulation(surfaceGraph);

    QObject::connect(inputhandler, &InputHandler::dragged,
                     simulation, &Simulation::drag);

    QWidget *container = QWidget::createWindowContainer(graph);

    if (!graph->hasContext()) {
        QMessageBox msgBox;
        msgBox.setText("Couldn't initialize the OpenGL context.");
        msgBox.exec();
        return -1;
    }

    QSize screenSize = graph->screen()->size();
    container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.6));
    container->setMaximumSize(screenSize);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);

    //! [1]
    QWidget *widget = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
//    QVBoxLayout *vLayout = new QVBoxLayout();

    QQuickWidget *m_quickWidget = new QQuickWidget;
    m_quickWidget->resize(300,300);
    m_quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView );
    m_quickWidget->setSource(QUrl("qrc:/qml/controlpanel.qml"));

    hLayout->addWidget(m_quickWidget, 1);
//    hLayout->addWidget(container, 1);
//    hLayout->addLayout(vLayout);
//    vLayout->setAlignment(Qt::AlignTop);
//    vLayout->
    //! [1]

    widget->setWindowTitle(QStringLiteral("Surface example"));

    QGroupBox *modelGroupBox = new QGroupBox(QStringLiteral("Model"));

    QRadioButton *simModelRB = new QRadioButton(widget);
    simModelRB->setText(QStringLiteral("Simulation"));
    simModelRB->setChecked(false);

    QRadioButton *sqrtSinModelRB = new QRadioButton(widget);
    sqrtSinModelRB->setText(QStringLiteral("Sqrt && Sin"));
    sqrtSinModelRB->setChecked(false);

    QRadioButton *heightMapModelRB = new QRadioButton(widget);
    heightMapModelRB->setText(QStringLiteral("Height Map"));
    heightMapModelRB->setChecked(false);

    QVBoxLayout *modelVBox = new QVBoxLayout;
    modelVBox->addWidget(simModelRB);
    modelVBox->addWidget(sqrtSinModelRB);
    modelVBox->addWidget(heightMapModelRB);
    modelGroupBox->setLayout(modelVBox);

    QGroupBox *selectionGroupBox = new QGroupBox(QStringLiteral("Selection Mode"));

    QRadioButton *modeNoneRB = new QRadioButton(widget);
    modeNoneRB->setText(QStringLiteral("No selection"));
    modeNoneRB->setChecked(false);

    QRadioButton *modeItemRB = new QRadioButton(widget);
    modeItemRB->setText(QStringLiteral("Item"));
    modeItemRB->setChecked(false);

    QRadioButton *modeSliceRowRB = new QRadioButton(widget);
    modeSliceRowRB->setText(QStringLiteral("Row Slice"));
    modeSliceRowRB->setChecked(false);

    QRadioButton *modeSliceColumnRB = new QRadioButton(widget);
    modeSliceColumnRB->setText(QStringLiteral("Column Slice"));
    modeSliceColumnRB->setChecked(false);

    QVBoxLayout *selectionVBox = new QVBoxLayout;
    selectionVBox->addWidget(modeNoneRB);
    selectionVBox->addWidget(modeItemRB);
    selectionVBox->addWidget(modeSliceRowRB);
    selectionVBox->addWidget(modeSliceColumnRB);
    selectionGroupBox->setLayout(selectionVBox);

    QSlider *axisMinSliderX = new QSlider(Qt::Horizontal, widget);
    axisMinSliderX->setMinimum(0);
    axisMinSliderX->setTickInterval(1);
    axisMinSliderX->setEnabled(true);
    QSlider *axisMaxSliderX = new QSlider(Qt::Horizontal, widget);
    axisMaxSliderX->setMinimum(1);
    axisMaxSliderX->setTickInterval(1);
    axisMaxSliderX->setEnabled(true);
    QSlider *axisMinSliderZ = new QSlider(Qt::Horizontal, widget);
    axisMinSliderZ->setMinimum(0);
    axisMinSliderZ->setTickInterval(1);
    axisMinSliderZ->setEnabled(true);
    QSlider *axisMaxSliderZ = new QSlider(Qt::Horizontal, widget);
    axisMaxSliderZ->setMinimum(1);
    axisMaxSliderZ->setTickInterval(1);
    axisMaxSliderZ->setEnabled(true);



    QGroupBox *colorGroupBox = new QGroupBox(QStringLiteral("Custom gradient"));

    QLinearGradient grBtoY(0, 0, 1, 500);
    grBtoY.setColorAt(0.0, Qt::black);
    grBtoY.setColorAt(0.02, Qt::blue);
    grBtoY.setColorAt(0.04, Qt::red);
    grBtoY.setColorAt(0.08, Qt::yellow);
    QPixmap pm(24, 100);
    QPainter pmp(&pm);
    pmp.setBrush(QBrush(grBtoY));
    pmp.setPen(Qt::NoPen);
    pmp.drawRect(0, 0, 24, 100);
    QPushButton *gradientBtoYPB = new QPushButton(widget);
    gradientBtoYPB->setIcon(QIcon(pm));
    gradientBtoYPB->setIconSize(QSize(24, 100));

    QLinearGradient grGtoR(0, 0, 1, 100);
    grGtoR.setColorAt(1.0, Qt::darkGreen);
    grGtoR.setColorAt(0.5, Qt::yellow);
    grGtoR.setColorAt(0.2, Qt::red);
    grGtoR.setColorAt(0.0, Qt::darkRed);
    pmp.setBrush(QBrush(grGtoR));
    pmp.drawRect(0, 0, 24, 100);
    QPushButton *gradientGtoRPB = new QPushButton(widget);
    gradientGtoRPB->setIcon(QIcon(pm));
    gradientGtoRPB->setIconSize(QSize(24, 100));

    QHBoxLayout *colorHBox = new QHBoxLayout;
    colorHBox->addWidget(gradientBtoYPB);
    colorHBox->addWidget(gradientGtoRPB);
    colorGroupBox->setLayout(colorHBox);

//    vLayout->addWidget(modelGroupBox);
//    vLayout->addWidget(selectionGroupBox);
//    vLayout->addWidget(new QLabel(QStringLiteral("Column range")));
//    vLayout->addWidget(axisMinSliderX);
//    vLayout->addWidget(axisMaxSliderX);
//    vLayout->addWidget(new QLabel(QStringLiteral("Row range")));
//    vLayout->addWidget(axisMinSliderZ);
//    vLayout->addWidget(axisMaxSliderZ);
//    vLayout->addWidget(colorGroupBox);

    widget->show();


    QObject::connect(heightMapModelRB, &QRadioButton::toggled,
                     surfaceGraph, &SurfaceGraph::enableHeightMapModel);
    QObject::connect(sqrtSinModelRB, &QRadioButton::toggled,
                     surfaceGraph, &SurfaceGraph::enableSqrtSinModel);
    QObject::connect(simModelRB, &QRadioButton::toggled,
                     surfaceGraph, &SurfaceGraph::enableSimulationModel);
    QObject::connect(modeNoneRB, &QRadioButton::toggled,
                     surfaceGraph, &SurfaceGraph::toggleModeNone);
    QObject::connect(modeItemRB,  &QRadioButton::toggled,
                     surfaceGraph, &SurfaceGraph::toggleModeItem);
    QObject::connect(modeSliceRowRB,  &QRadioButton::toggled,
                     surfaceGraph, &SurfaceGraph::toggleModeSliceRow);
    QObject::connect(modeSliceColumnRB,  &QRadioButton::toggled,
                     surfaceGraph, &SurfaceGraph::toggleModeSliceColumn);
    QObject::connect(axisMinSliderX, &QSlider::valueChanged,
                     surfaceGraph, &SurfaceGraph::adjustXMin);
    QObject::connect(axisMaxSliderX, &QSlider::valueChanged,
                     surfaceGraph, &SurfaceGraph::adjustXMax);
    QObject::connect(axisMinSliderZ, &QSlider::valueChanged,
                     surfaceGraph, &SurfaceGraph::adjustZMin);
    QObject::connect(axisMaxSliderZ, &QSlider::valueChanged,
                     surfaceGraph, &SurfaceGraph::adjustZMax);
//    QObject::connect(themeList, SIGNAL(currentIndexChanged(int)),
//                     surfaceGraph, SLOT(changeTheme(int)));
    QObject::connect(gradientBtoYPB, &QPushButton::pressed,
                     surfaceGraph, &SurfaceGraph::setBlackToYellowGradient);
    QObject::connect(gradientGtoRPB, &QPushButton::pressed,
                     surfaceGraph, &SurfaceGraph::setGreenToRedGradient);

    surfaceGraph->setAxisMinSliderX(axisMinSliderX);
    surfaceGraph->setAxisMaxSliderX(axisMaxSliderX);
    surfaceGraph->setAxisMinSliderZ(axisMinSliderZ);
    surfaceGraph->setAxisMaxSliderZ(axisMaxSliderZ);

//    heightMapModelRB->setChecked(true);
    simModelRB->setChecked(true);
    modeItemRB->setChecked(true);

    return app.exec();
}

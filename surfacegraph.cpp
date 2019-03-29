#include "surfacegraph.h"
#include "inputhandler.h"
#include "simulation.h"

#include <QtDataVisualization/QValue3DAxis>
#include <QtDataVisualization/Q3DTheme>
#include <QtDataVisualization/QCustom3DItem>
#include <QtGui/QImage>
#include <QtCore/qmath.h>

using namespace QtDataVisualization;

static const float verticalRange = 8.0f;
static const float horizontalRange = verticalRange;
static const float ellipse_a = horizontalRange / 3.0f;
static const float ellipse_b = verticalRange;
static const float doublePi = float(M_PI) * 2.0f;
static const float radiansToDegrees = 360.0f / doublePi;
static const float animationFrames = 30.0f;
static const double gridSize = 100.0;

SurfaceGraph::SurfaceGraph(Q3DSurface *surface, InputHandler *inputhandler):
    m_graph(surface)
{
    surface->setActiveInputHandler(inputhandler);

    m_graph->setAxisX(new QValue3DAxis);
    m_graph->setAxisY(new QValue3DAxis);
    m_graph->setAxisZ(new QValue3DAxis);

    m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);
    m_graph->activeTheme()->setType(Q3DTheme::ThemeEbony);
    m_graph->activeTheme()->setGridEnabled(false);
    m_graph->activeTheme()->setBackgroundEnabled(false);
    m_graph->activeTheme()->setLabelTextColor("transparent");

    m_simSinProxy = new QSurfaceDataProxy();
    m_simSinSeries = new QSurface3DSeries(m_simSinProxy);


    this->enableSimulationModel(true);
}

SurfaceGraph::~SurfaceGraph()
{
    delete m_graph;
}

void SurfaceGraph::resetData(QSurfaceDataArray *dataArray)
{
    m_simSinProxy->resetArray(dataArray);
}

void SurfaceGraph::generateData()
{

    QImage color = QImage(2, 2, QImage::Format_RGB32);
           color.fill(Qt::red);
    for (int i = 0; i < gridSize; i++) {

        for (int j = 0; j < gridSize; j++) {
            QQuaternion rotation = QQuaternion::fromAxisAndAngle(0.0f, 0.0f, 0.0f, 0);



            QCustom3DItem *item = new QCustom3DItem(":/narrowarrow.obj",
                                                    QVector3D((1.0f * i), 0.02f, (1.0f * j)),
                                                    QVector3D(0.01f, 0.01f, 0.01f),
                                                    rotation,
                                                    color);


            item->setRotation(QQuaternion::fromAxisAndAngle(0.5f, 0.0f, 1.0f, 90));
            //qDebug() << i << " - " << j << " : " << (0.16 * i - 8) << " " << (0.16 * j - 8);

            m_arrows.append(item);

            m_graph->addCustomItem(item);
        }
    }


}


QVector<QCustom3DItem*> SurfaceGraph::getArrows(){
    return m_arrows;
}

void SurfaceGraph::enableSimulationModel(bool enable)
{
    m_simSinSeries->setDrawMode(QSurface3DSeries::DrawSurface);
    m_simSinSeries->setFlatShadingEnabled(false);
    m_simSinSeries->setItemLabelVisible(false);


    m_graph->axisX()->setRange(-1.0f, 201.0f);
    m_graph->axisY()->setRange(0.0f, 0.2f);
    m_graph->setAspectRatio(20);
    m_graph->axisZ()->setRange(-1.0f, 201.0f);

    m_graph->addSeries(m_simSinSeries);

    m_graph->axisX()->setLabelFormat("%.2f");
    m_graph->axisZ()->setLabelFormat("%.2f");

//        m_graph->axisX()->setRange(0.0f, 10.0f);
//        m_graph->axisY()->setRange(0.0f, 1.0f);
//        m_graph->axisZ()->setRange(0.0f, 10.0f);

    m_graph->axisX()->setLabelAutoRotation(30);
    m_graph->axisY()->setLabelAutoRotation(90);
    m_graph->axisZ()->setLabelAutoRotation(30);



//        // Reset range sliders for Sqrt&Sin
//        m_rangeMinX = simMin;
//        m_rangeMinZ = simMin;
//        m_stepX = 1;
//        m_stepZ = 1;

//        m_axisMinSliderX->setMaximum(DIM - 2);
//        m_axisMinSliderX->setValue(0);
//        m_axisMaxSliderX->setMaximum(DIM - 1);
//        m_axisMaxSliderX->setValue(DIM - 1);

//        m_axisMinSliderZ->setMaximum(DIM - 2);
//        m_axisMinSliderZ->setValue(0);
//        m_axisMaxSliderZ->setMaximum(DIM - 1);
//        m_axisMaxSliderZ->setValue(DIM - 1);
}

void SurfaceGraph::drawWireFrame(bool wire_frame)
{
    if (wire_frame) {
        m_simSinSeries->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
    } else {
        m_simSinSeries->setDrawMode(QSurface3DSeries::DrawSurface);
    }
}

void SurfaceGraph::adjustXMin(int min)
{
    float minX = m_stepX * float(min) + m_rangeMinX;

    int max = m_axisMaxSliderX->value();
    if (min >= max) {
        max = min + 1;
        m_axisMaxSliderX->setValue(max);
    }
    float maxX = m_stepX * max + m_rangeMinX;

    setAxisXRange(minX, maxX);
}

void SurfaceGraph::adjustXMax(int max)
{
    float maxX = m_stepX * float(max) + m_rangeMinX;

    int min = m_axisMinSliderX->value();
    if (max <= min) {
        min = max - 1;
        m_axisMinSliderX->setValue(min);
    }
    float minX = m_stepX * min + m_rangeMinX;

    setAxisXRange(minX, maxX);
}

void SurfaceGraph::adjustZMin(int min)
{
    float minZ = m_stepZ * float(min) + m_rangeMinZ;

    int max = m_axisMaxSliderZ->value();
    if (min >= max) {
        max = min + 1;
        m_axisMaxSliderZ->setValue(max);
    }
    float maxZ = m_stepZ * max + m_rangeMinZ;

    setAxisZRange(minZ, maxZ);
}

void SurfaceGraph::adjustZMax(int max)
{
    float maxX = m_stepZ * float(max) + m_rangeMinZ;

    int min = m_axisMinSliderZ->value();
    if (max <= min) {
        min = max - 1;
        m_axisMinSliderZ->setValue(min);
    }
    float minX = m_stepZ * min + m_rangeMinZ;

    setAxisZRange(minX, maxX);
}

//! [5]
void SurfaceGraph::setAxisXRange(float min, float max)
{
    m_graph->axisX()->setRange(min, max);
}

void SurfaceGraph::setAxisZRange(float min, float max)
{
    m_graph->axisZ()->setRange(min, max);
}



void SurfaceGraph::setBlackToYellowGradient()
{
    QLinearGradient gr;
    gr.setColorAt(0.0, Qt::black);
    gr.setColorAt(0.33, Qt::blue);
    gr.setColorAt(0.67, Qt::red);
    gr.setColorAt(1.0, Qt::yellow);

    m_graph->seriesList().at(0)->setBaseGradient(gr);
    m_graph->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
}

void SurfaceGraph::setGreenToRedGradient()
{
    QLinearGradient gr;
    gr.setColorAt(0.0, Qt::darkGreen);
    gr.setColorAt(0.5, Qt::yellow);
    gr.setColorAt(0.8, Qt::red);
    gr.setColorAt(1.0, Qt::darkRed);

    m_graph->seriesList().at(0)->setBaseGradient(gr);
    m_graph->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
}


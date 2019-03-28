#include "scattergraph.h"
#include <QtDataVisualization/qscatterdataproxy.h>
#include <QtDataVisualization/qvalue3daxis.h>
#include <QtDataVisualization/q3dscene.h>
#include <QtDataVisualization/q3dcamera.h>
#include <QtDataVisualization/qscatter3dseries.h>
#include <QtDataVisualization/q3dtheme.h>
#include <QtDataVisualization/QCustom3DItem>
#include <QtDataVisualization/QValue3DAxis>
#include <QtDataVisualization/Q3DTheme>
#include <QtGui/QImage>
#include <QtCore/qmath.h>
#include "inputhandler.h"

using namespace QtDataVisualization;

static const float verticalRange = 8.0f;
static const float horizontalRange = verticalRange;
static const float ellipse_a = horizontalRange / 3.0f;
static const float ellipse_b = verticalRange;
static const float doublePi = float(M_PI) * 2.0f;
static const float radiansToDegrees = 360.0f / doublePi;
static const float animationFrames = 30.0f;

ScatterGraph::ScatterGraph(Q3DScatter *scatter, InputHandler *inputhandler)
    : m_graph(scatter),
      m_fieldLines(200),
      m_arrowsPerLine(200),
      m_magneticField(new QScatter3DSeries),
      m_sun(new QCustom3DItem),
      m_magneticFieldArray(0),
      m_angleOffset(0.0f),
      m_angleStep(doublePi / m_arrowsPerLine / animationFrames)
{
    m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);
    m_graph->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetFront);

    m_surfaceDataProxy = new QSurfaceDataProxy(m_magneticField);

    // Dikte
    m_magneticField->setItemSize(0.06f);

    m_magneticField->setMesh(QAbstract3DSeries::MeshUserDefined);
    m_magneticField->setUserDefinedMesh(QStringLiteral(":/narrowarrow.obj"));
    m_magneticField->setBaseColor(QColor(255, 0, 0));


    QImage sunColor = QImage(2, 2, QImage::Format_RGB32);
    QLinearGradient fieldGradient(0, 0, 16, 1024);
    fieldGradient.setColorAt(0.0, Qt::black);
    fieldGradient.setColorAt(1.0, Qt::white);


    m_magneticField->meshRotation();
    fieldGradient.setColorAt(0.0, Qt::red);
    fieldGradient.setColorAt(1.0, Qt::darkRed);
    m_magneticField->setColorStyle(Q3DTheme::ColorStyleUniform);
    //m_magneticField->setColorStyle()
    /*QLinearGradient fieldGradient(0, 0, 16, 1024);
    fieldGradient.setColorAt(0.0, Qt::black);
    fieldGradient.setColorAt(1.0, Qt::white);
    m_magneticField->setBaseGradient(fieldGradient);
    m_magneticField->setColorStyle(Q3DTheme::ColorStyleRangeGradient);*/

    // For 'sun' we use a custom large sphere
    /*m_sun->setScaling(QVector3D(0.07f, 0.07f, 0.07f));
    m_sun->setMeshFile(QStringLiteral(":/mesh/largesphere.obj"));
    QImage sunColor = QImage(2, 2, QImage::Format_RGB32);
    sunColor.fill(QColor(0xff, 0xbb, 0x00));
    m_sun->setTextureImage(sunColor);*/

    QQuaternion gRotation = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 1.0f, 180);
    m_magneticField->setMeshRotation(gRotation);
    m_graph->addSeries(m_magneticField);
    //m_graph->addCustomItem(m_sun);

    // Configure the axes according to the data
    m_graph->axisX()->setRange(-horizontalRange, horizontalRange);
    m_graph->axisY()->setRange(0, verticalRange);
    m_graph->axisZ()->setRange(-horizontalRange, horizontalRange);
    m_graph->axisX()->setSegmentCount(int(horizontalRange));
    m_graph->axisZ()->setSegmentCount(int(horizontalRange));

    QObject::connect(&m_rotationTimer, &QTimer::timeout, this,
                     &ScatterGraph::triggerRotation);

    //toggleRotation();
    //generateData();
    scatter->setActiveInputHandler(inputhandler);
}

ScatterGraph::~ScatterGraph()
{
    delete m_graph;
}

void ScatterGraph::generateData()
{


    if (!m_magneticFieldArray)
        m_magneticFieldArray = new QScatterDataArray;

    int arraySize = m_fieldLines * m_arrowsPerLine;
    if (arraySize != m_magneticFieldArray->size())
        m_magneticFieldArray->resize(arraySize);

    QScatterDataItem *ptrToDataArray = &m_magneticFieldArray->first();
    for (int i = 0; i < m_fieldLines; i++) {

        for (int j = 0; j < m_arrowsPerLine; j++) {

            float verticalAngle = ((doublePi * j) / m_arrowsPerLine) + m_angleOffset;
            QQuaternion yRotation = QQuaternion::fromAxisAndAngle(0.0f, 0.0f, 1.0f, verticalAngle * radiansToDegrees);

            //qDebug() << i << " - " << j << " : " << (0.16 * i - 8) << " " << (0.16 * j - 8);
            ptrToDataArray->setPosition(QVector3D((0.16 * i - 8), 0, (0.16 * j - 8)));
            ptrToDataArray->setRotation(yRotation);
            ptrToDataArray++;
        }
    }
    m_magneticField->dataProxy()->resetArray(m_magneticFieldArray);
}

void ScatterGraph::resetData(QScatterDataArray *dataArray){
    m_magneticField->dataProxy()->resetArray(dataArray);
}


void ScatterGraph::setFieldLines(int lines)
{
    m_fieldLines = lines;
    generateData();
}

void ScatterGraph::setArrowsPerLine(int arrows)
{
    m_angleOffset = 0.0f;
    m_angleStep = doublePi / m_arrowsPerLine / animationFrames;
    qDebug() << m_angleStep;
    m_arrowsPerLine = arrows;
    generateData();
}

void ScatterGraph::triggerRotation()
{
    m_angleOffset += m_angleStep;
    generateData();
}

void ScatterGraph::toggleSun()
{
    m_sun->setVisible(!m_sun->isVisible());
}

void ScatterGraph::toggleRotation()
{
    if (m_rotationTimer.isActive())
        m_rotationTimer.stop();
    else
        m_rotationTimer.start(15);
}

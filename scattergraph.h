#ifndef SCATTERGRAPH_H
#define SCATTERGRAPH_H

#include <QtDataVisualization/q3dscatter.h>
#include <QtDataVisualization/qscatterdataproxy.h>
#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>
#include <QtCore/QTimer>
#include "inputhandler.h"

using namespace QtDataVisualization;

class ScatterGraph : public QObject
{
    Q_OBJECT
public:
    explicit ScatterGraph(Q3DScatter *scatter, InputHandler *inputhandler);
    ~ScatterGraph();

    void resetData(QScatterDataArray *dataArray);
    void generateData();

public Q_SLOTS:
    void setFieldLines(int lines);
    void setArrowsPerLine(int arrows);
    void toggleRotation();
    void triggerRotation();
    void toggleSun();
private:
    Q3DScatter *m_graph;
    QTimer m_rotationTimer;
    int m_fieldLines;
    int m_arrowsPerLine;
    QScatter3DSeries *m_magneticField;
    QCustom3DItem *m_sun;
    QScatterDataArray *m_magneticFieldArray;
    QSurfaceDataProxy *m_surfaceDataProxy;
    float m_angleOffset;
    float m_angleStep;
};

#endif

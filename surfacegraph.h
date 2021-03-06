#ifndef SURFACEGRAPH_H
#define SURFACEGRAPH_H

#include "inputhandler.h"

#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QHeightMapSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>
#include <QtWidgets/QSlider>

using namespace QtDataVisualization;

class SurfaceGraph : public QObject
{
    Q_OBJECT
    enum GradientState {
        StateGreenToRed = 0,
        StateBlackToYellow = 1,
        StateIsoLine = 2,
        CustomIsoLine = 3
    };
    public:
        explicit SurfaceGraph(Q3DSurface *surface, InputHandler *inputhandler);
        ~SurfaceGraph();

        void resetData(QSurfaceDataArray *dataArray);

        void enableSimulationModel(bool enable);

        //! [0]
        void toggleModeNone() { m_graph->setSelectionMode(QAbstract3DGraph::SelectionNone); }
        void toggleModeSliceRow() { m_graph->setSelectionMode(QAbstract3DGraph::SelectionItemAndRow
                                                              | QAbstract3DGraph::SelectionSlice); }
        void toggleModeSliceColumn() { m_graph->setSelectionMode(QAbstract3DGraph::SelectionItemAndColumn
                                                                 | QAbstract3DGraph::SelectionSlice); }
        //! [0]


        void setAxisMinSliderX(QSlider *slider) { m_axisMinSliderX = slider; }
        void setAxisMaxSliderX(QSlider *slider) { m_axisMaxSliderX = slider; }
        void setAxisMinSliderZ(QSlider *slider) { m_axisMinSliderZ = slider; }
        void setAxisMaxSliderZ(QSlider *slider) { m_axisMaxSliderZ = slider; }

        void adjustXMin(int min);
        void adjustXMax(int max);
        void adjustZMin(int min);
        void adjustZMax(int max);
        void clearData();
        void generateData();
        void generateRandomGridData(int size);
        QVector<QCustom3DItem*> getArrows();
        void setHeightArrows(double height);
    public Q_SLOTS:
        void hueRotation(double);
        void isolineRotation(double);
        void scaleGraph(double);
        void drawWireFrame(bool);
        void enableFlatShading(bool);
        void setBlackToYellowGradient();
        void setGreenToRedGradient();
        void setIsoLineGradient();
        void setCustomIsolineMax(double val);
        void setCustomIsolineMin(double val);
        void setCustomIsolineInterval(int val);
        void setCustomIsoLineGradient();
        void enableAxis(bool val);

        void toggleModeItem() { m_graph->setSelectionMode(QAbstract3DGraph::SelectionItem); }
    private:
        Q3DSurface *m_graph;
        QHeightMapSurfaceDataProxy *m_heightMapProxy;
        QSurfaceDataProxy *m_sqrtSinProxy;
        QSurface3DSeries *m_heightMapSeries;
        QSurface3DSeries *m_sqrtSinSeries;

        QSurfaceDataProxy *m_simSinProxy;
        QSurface3DSeries *m_simSinSeries;

        QVector<QCustom3DItem*> m_arrows;

        double customIsolineMin = 0.5;
        double customIsolineMax = 0.9;
        int customIsolineInterval = 3;
        QSlider *m_axisMinSliderX;
        QSlider *m_axisMaxSliderX;
        QSlider *m_axisMinSliderZ;
        QSlider *m_axisMaxSliderZ;
        float m_rangeMinX;
        float m_rangeMinZ;
        float m_stepX;
        float m_stepZ;
        int m_heightMapWidth;
        int m_heightMapHeight;

        float hue_rotation = 0;
        float isoline_rotation = 0;
        int active_gradient;
        int scale_graph = 20;
        double glyphHeight = 0.5;

        void setAxisXRange(float min, float max);
        void setAxisZRange(float min, float max);
        void fillSqrtSinProxy();
        void updateGradient();
        float calcHue(float val);
        float calcIsolineHue(float val);
};

#endif

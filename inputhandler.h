#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <QtDataVisualization/Q3DInputHandler>
#include <QtDataVisualization/QAbstract3DGraph>
#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurface3DSeries>

using namespace QtDataVisualization;

class InputHandler : public Q3DInputHandler
{
    Q_OBJECT
    enum InputState {
        StateNormal = 0,
        StateDragging,
    };

    public:
        explicit InputHandler(Q3DSurface *graph = nullptr, QObject *parent = 0);
        virtual ~InputHandler();

        virtual void mousePressEvent(QMouseEvent *event, const QPoint &mousePos);
        virtual void mouseMoveEvent(QMouseEvent *event, const QPoint &mousePos);
        virtual void mouseReleaseEvent(QMouseEvent *event, const QPoint &mousePos);

    signals:
        void dragged(int X, int Y, float dx, float dy);

    private:
        void handleElementSelected(QAbstract3DGraph::ElementType type);
        void handleDragging();

    private:
        bool mousePressed;
        InputState state;
        float speedModifier;
        Q3DSurface *m_graph;
};

#endif

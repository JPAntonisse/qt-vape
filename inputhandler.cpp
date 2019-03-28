#include "inputhandler.h"
#include <QtCore/qmath.h>
#include <Q3DSurface>
#include <Q3DScatter>

using namespace QtDataVisualization;

Q_DECLARE_METATYPE(QSurface3DSeries *)


const float m_speedmodifier = 20.0f;


InputHandler::~InputHandler()
{
}

InputHandler::InputHandler(QAbstract3DGraph *graph, QObject *parent) :
    Q3DInputHandler(parent),
    mousePressed(false),
    speedModifier(15.0f),
    m_graph(graph)
{
    // Connect to the item selection signal from graph
    connect(
        graph, &QAbstract3DGraph::selectedElementChanged,
        this, &InputHandler::handleElementSelected
        );
}

void InputHandler::mousePressEvent(QMouseEvent *event, const QPoint &mousePos)
{
    Q3DInputHandler::mousePressEvent(event, mousePos);
    if (Qt::LeftButton == event->button())
        mousePressed = true;
}

void InputHandler::mouseMoveEvent(QMouseEvent *event, const QPoint &mousePos)
{
    if (mousePressed && state != StateNormal) {
        m_graph->scene()->setSelectionQueryPosition(mousePos);
        setPreviousInputPos(inputPosition());
        setInputPosition(mousePos);
        handleDragging();
    } else {
        Q3DInputHandler::mouseMoveEvent(event, mousePos);
    }
}

void InputHandler::mouseReleaseEvent(QMouseEvent *event, const QPoint &mousePos)
{
    Q3DInputHandler::mouseReleaseEvent(event, mousePos);
    mousePressed = false;
    state = StateNormal;
}


void InputHandler::handleElementSelected(QAbstract3DGraph::ElementType type)
{
    switch (type) {
    case QAbstract3DGraph::ElementSeries:
        state = StateDragging;
        break;
    default:
        state = StateNormal;
        break;
    }
}

void InputHandler::handleDragging()
{
    float xDistance,yDistance = 0.0f;

    int id;
    QPoint selectedPoint;
    QScatterDataItem item;
    if ( dynamic_cast<Q3DSurface*>( m_graph ) ){
        selectedPoint = dynamic_cast<Q3DSurface*>( m_graph )->selectedSeries()->selectedPoint();
    }
    if( dynamic_cast<Q3DScatter*>( m_graph ) ){
        id = dynamic_cast<Q3DScatter*>( m_graph )->selectedSeries()->selectedItem();
        item = *dynamic_cast<Q3DScatter*>( m_graph )->selectedSeries()->dataProxy()->itemAt(id);
    }

    // Get scene orientation from active camera
    float xRotation = scene()->activeCamera()->xRotation();
    float yRotation = scene()->activeCamera()->yRotation();

    // Calculate directional drag multipliers based on rotation
    float xMulX = qCos(qDegreesToRadians(xRotation));
    float xMulY = -qSin(qDegreesToRadians(xRotation));

    // Get the drag amount
    QPoint move = inputPosition() - previousInputPos();

    // Adjust axes
    switch (state) {
        case StateDragging: {
            int xMove = move.x();
            int yMove = -move.y();

            xDistance = (xMove * xMulX - yMove * xMulY) / m_speedmodifier;
            yDistance = (xMove * xMulY + yMove * xMulX) / m_speedmodifier;

            if(selectedPoint.x() == NULL){
                emit(dragged(item.x(), item.z(),xDistance, yDistance));
            }
            else emit(dragged(selectedPoint.x(), selectedPoint.y(),xDistance, yDistance));
            break;
        }
        default:
            break;
    }
}

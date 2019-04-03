#include "datacontroller.h"

DataController::DataController(SurfaceGraph *surfaceGraph) : surfaceGraph(surfaceGraph), container(container)
{
    //viewType = 's';

}


void DataController::setView(char type){
    // View Type, s = surfaceGraph, d = scatterDataModifier
    viewType = type;


}

void DataController::setData(QSurfaceDataArray *dataArray){
    //WORK TO DO
    setDataSurfaceGraph(dataArray);
}

void DataController::setDataSurfaceGraph(QSurfaceDataArray *dataArray){
    surfaceGraph->resetData(dataArray);
}

ScatterGraph* DataController::getScatterGraph(){
    return scatterGraph;
}

SurfaceGraph* DataController::getSurfaceGraph(){
    return surfaceGraph;
}

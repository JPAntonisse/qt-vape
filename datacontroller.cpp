#include "datacontroller.h"

DataController::DataController(QWidget *container, SurfaceGraph *surfaceGraph, ScatterGraph *scatterGraph) : surfaceGraph(surfaceGraph), scatterGraph(scatterGraph), container(container)
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
    //setDataScatterGraph(dataArray);

}

void DataController::setDataSurfaceGraph(QSurfaceDataArray *dataArray){
    surfaceGraph->resetData(dataArray);
}

void DataController::setDataScatterGraph(QScatterDataArray *dataArray){
    //scatterGraph->setProperty()
    //scatterGraph->
}

ScatterGraph* DataController::getScatterGraph(){
    return scatterGraph;
}

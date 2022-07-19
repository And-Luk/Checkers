#include "manager.h"

Manager::Manager(QObject *parent) : QObject(parent){

}

void Manager::slotRepeatMoveLabel(QPoint position, QPoint newPosition){
    //todo


    //todo
    if (true) {
        emit signalMoveLabel(position, newPosition);
    }
}



void Manager::MakeFigures(unsigned int Where, unsigned int Color, unsigned int Who){
    emit signalMakeFigures(Where, Color, Who);
    emit signalViewFiguresOnBoard(true);
}

void Manager::slotRun(){
    MakeFigures(4293922815,4293918720,0); //267390960,267386880,0
    emit signalWhoIsFirstPlaer("white");
    emit signalUnblockedPlayer(1);
}


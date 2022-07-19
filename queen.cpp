#include "queen.h"


Queen::Queen(bool IsWhite, bool IsQueen, QPoint Position):Figure(IsWhite, IsQueen, Position){}


Queen::~Queen(){}


void Queen::calculate(ViewLabel*  doubArrayViewLabel[8][8]){
    clearPathway();
    QVector<Pathway> pathway;
    pathway<<queenBeats(getPosition(),getIsWhite(),doubArrayViewLabel);

    if (pathway.empty()) {pathway<<emptyALLWay(getPosition(),doubArrayViewLabel);}


    setVPathway(pathway);
}

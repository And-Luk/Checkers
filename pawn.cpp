#include "pawn.h"

Pawn::Pawn(bool IsWhite, bool IsQueen, QPoint Position):Figure(IsWhite, IsQueen, Position){}


Pawn::~Pawn(){}


void Pawn::setPosition(QPoint Position){
    if (getIsFirstPlayr() && (Position.y()==0)) {
        Figure::setPosition(Position);
        emit signalReplaceFigure(this);
        return;
    }
    if (!getIsFirstPlayr() && (Position.y()==7)) {
        Figure::setPosition(Position);
        emit signalReplaceFigure(this);
        return;
    }
    Figure::setPosition(Position);
}


void Pawn::calculate(ViewLabel*  doubArrayViewLabel[8][8]){
    clearPathway();
    QVector<Pathway> pathway;
    pathway<<pawnBeats(getPosition(),getIsWhite(), getIsFirstPlayr(), doubArrayViewLabel);
    if (pathway.empty()) { setVPathway(pawnStep(doubArrayViewLabel)); }
    else {setVPathway(pathway); }

}


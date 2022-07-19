#include "figurechild.h"

FigureChild::FigureChild(bool isWhite, bool isTheQueen,  QPoint position): Figure(isWhite, isTheQueen, position){

}


QVector<Pathway>& FigureChild::getPathway(){

    return pathway;
}


void FigureChild::setPathway(QVector<Pathway> const pathW){
    pathway.clear();
    pathway<<pathW;
}


void FigureChild::setIsWhite(bool IsWhite){ this->isWhite=IsWhite;}
bool FigureChild::getIsWhite()const{return this->isWhite;}

void FigureChild::setIsQueen(bool IsQueen){this->isQueen=IsQueen;}
bool FigureChild::getIsQueen()const{return this->isQueen;}

void FigureChild::setIsFirstPlayr(bool FirstPlayr){this->isFirstPlayer=FirstPlayr;}
bool FigureChild::getIsFirstPlayr()const{return this->isFirstPlayer;}

void FigureChild::setCurentPosition(QPoint CurentPosition){ this->curentPosition=CurentPosition;}
QPoint FigureChild::getCurentPosition()const{return this->curentPosition;}

void FigureChild::setPTimeLabel(TimeLabel* pTimeLabel){ this->pTimeLabel=pTimeLabel;}
TimeLabel* FigureChild::getPTimeLabel(){return this->pTimeLabel;}

void FigureChild::clearPathway(){pathway.clear();}










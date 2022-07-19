#include "pathway.h"

Pathway::Pathway(QPoint Position, QVector<QPoint> vDownedPnt): position{Position}{
    countDownedPoints=0;
    if (!vDownedPnt.empty()) {
        countDownedPoints+=vDownedPnt.size();
        vDownedPoints<<vDownedPnt;
    }
}


Pathway::Pathway(QPoint Position): position{Position},countDownedPoints{0}{}


void Pathway::setPosition(QPoint pos){position=pos;}
QPoint  Pathway::getPosition()const{return position;}


void  Pathway::setCount(int countDownedFig){ countDownedPoints = countDownedFig;}
int  Pathway::getCount()const{return countDownedPoints;}


void  Pathway::setDownedPoints(QPoint DownedPoints){ vDownedPoints<<DownedPoints;}
void  Pathway::setDownedPoints(QVector<QPoint> DownedPoints){ vDownedPoints<<DownedPoints;}
QVector<QPoint>  Pathway::getDownedPoints(){return vDownedPoints;}


void Pathway::setDirection(Direction direct){direction=direct;}
Direction  Pathway::getDirection()const{return direction;}


Pathway& Pathway::operator+(Pathway& pathwayAfter){
    countDownedPoints+=pathwayAfter.countDownedPoints;
    direction = pathwayAfter.direction;
    //position = pathwayAfter.position;
    vDownedPoints << pathwayAfter.vDownedPoints;
    return *this;
}

//setDirection(pathwayAfter.getDirection()); // может понадобиться начальное направление
//setPosition(pathwayAfter.getPosition());
//setDownedPoints(pathwayAfter.getDownedPoints());

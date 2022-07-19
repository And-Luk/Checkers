#pragma once

#include<QPoint>

class TranslatorArray
{
private:
    QPoint* arrayQPointTr[64];
    int optimal_X_Position(QPoint** const, const QPoint, const int,const int);
    int optimal_Y_Position(QPoint** const, const QPoint, const int,const int,const int);

public:
    TranslatorArray(int displacement,int step); //displacement off 0,0
    ~TranslatorArray();

    QPoint translateFrom(QPoint);
    QPoint translateBack(QPoint);

};


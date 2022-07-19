#pragma once

#include<QPoint>

class RealCoordinates
{
public:
    RealCoordinates(int displacement,int step);
    ~RealCoordinates();

    QPoint virtualToReal(QPoint);
    QPoint realToVirtual(QPoint);

private:
    QPoint* arrayQPointTr[64];
    int optimal_XPosition(QPoint** const, const QPoint, const int,const int);
    int optimal_YPosition(QPoint** const, const QPoint, const int,const int,const int);

};


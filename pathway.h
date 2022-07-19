#pragma once

#include<QVector>
#include<ViewLabel.h>

class Pathway
{
public:
    Pathway(QPoint position, QVector<QPoint> vDownedPnt);
    Pathway(QPoint position);
    Pathway() = delete;

    Pathway& operator+( Pathway&  pathway2);

    void setPosition(QPoint position);
    QPoint getPosition()const;

    void setCount(int countDownedPoints);
    int getCount()const;

    void setDownedPoints(QPoint DownedPoints);
    void setDownedPoints(QVector<QPoint> DownedPoints);
    QVector<QPoint> getDownedPoints();

    void setDirection(Direction direct);
    Direction getDirection()const;

private:
    QPoint position;
    int countDownedPoints;
    QVector<QPoint> vDownedPoints;
    Direction direction; // for future
};

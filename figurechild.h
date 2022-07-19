#pragma once

#include<pathway.h>

class FigureChild:public Figure
{
public:
    FigureChild(bool isWhite, bool isTheQueen,  QPoint position);
    FigureChild() = delete;

    void setIsWhite(bool IsWhite);
    bool getIsWhite()const;

    void setIsQueen(bool IsQueen);
    bool getIsQueen()const;

    void setIsFirstPlayr(bool FirstPlayr);
    bool getIsFirstPlayr()const;

    void setCurentPosition(QPoint CurentPosition);
    QPoint getCurentPosition()const;

    void setPTimeLabel(TimeLabel* pTimeLabel);
    TimeLabel * getPTimeLabel();

    void setPathway(QVector<Pathway> const pathW);
    QVector<Pathway>& getPathway();
    void clearPathway();

private:
    QVector<Pathway> pathway;

};

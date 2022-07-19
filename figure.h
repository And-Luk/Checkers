#pragma once

#include<pathway.h>


class Figure{
public:

    virtual ~Figure();
    Figure(const Figure&) = delete;
    Figure& operator=(const Figure&)= delete;

    void setIsWhite(bool IsWhite);
    bool getIsWhite()const;

    void setIsQueen(bool IsQueen);
    bool getIsQueen()const;

    void setIsFirstPlayr(bool IsFirstPlayr);
    bool getIsFirstPlayr()const;

    void setIsBlokedState(bool IsBlokedState);
    bool getIsBlokedState()const;

    virtual void setPosition(QPoint Position);
    QPoint getPosition()const;

    void clearPathway();
    void setVPathway(QVector<Pathway>);
    void setVPathway(Pathway);
    QVector<Pathway> getVPathway()const;

//is it possible to beat from a position in the direction

    bool isItPossibleToBeat (QPoint Position, const Direction direction, const bool IsWhite, ViewLabel* doubArrayViewLabel[8][8])const;

    QVector<Pathway> pawnStep  (ViewLabel* doubArrayViewLabel[8][8])const;
    QVector<Pathway> pawnBeats (QPoint Position, const bool IsWhite, const bool IsFirstPlayer, ViewLabel* doubArrayViewLabel[8][8])const;

    QVector<Pathway> emptyWay  (QPoint Position, const Direction direction, ViewLabel* doubArrayViewLabel[8][8])const;
    QVector<Pathway> emptyALLWay  (QPoint Position, ViewLabel* doubArrayViewLabel[8][8])const;
    QVector<Pathway> queenBeats(QPoint Position, const bool IsWhite, ViewLabel* doubArrayViewLabel[8][8])const;
    QVector<Pathway> queenDirectionBeats (const QPoint Position, const Direction direction, const bool IsWhite, ViewLabel* doubArrayViewLabel[8][8])const;


    virtual void calculate(ViewLabel* doubArrayViewLabel[8][8])=0;


protected:
    Figure(bool IsWhite, bool IsQueen, QPoint Position);




private:

    bool isWhite{true};
    bool isQueen{false};
    bool isFirstPlayer{false};
    bool isBlokedState{true};
    QPoint position;
    QVector<Pathway> vPathway;


};

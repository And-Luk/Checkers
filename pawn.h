#pragma once

#include<figure.h>
#include<QObject>

class Pawn:public QObject, public Figure{
    Q_OBJECT
public:
    Pawn(bool IsWhite, bool IsQueen, QPoint Position);
    ~Pawn();
    void setPosition(QPoint Position) override;
    void calculate( ViewLabel* doubArrayViewLabel[8][8]) override;


signals:
    void signalReplaceFigure(Figure* I_AM);


};


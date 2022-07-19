#pragma once
#include<figure.h>

class Queen:public Figure
{
public:
    Queen(bool IsWhite, bool IsQueen, QPoint Position);
    ~Queen();
    void calculate(ViewLabel*  doubArrayViewLabel[8][8]) override;

};


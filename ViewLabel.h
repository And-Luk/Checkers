#pragma once

#include<QPoint>

enum Direction{Upper_Left, Upper_Right, Down_Left, Down_Right};

enum ViewQLabel{whiteCh,whiteQ,blackCh,blackQ};

struct ViewLabel{
public:
    ViewLabel(){};
    ViewLabel(QPoint Position,ViewQLabel ViewLabel):position{Position},viewQLabel{ViewLabel}{};
    QPoint getPosition()const{return position;};
    void setPosition(QPoint Position){position = Position;};
    ViewQLabel getViewQLabel()const{return viewQLabel;};
    void setViewQLabel(ViewQLabel ViewQLabel){viewQLabel = ViewQLabel;};

    void setIsWhite(bool IsWhite){isWhite=IsWhite;}
    bool getIsWhite()const{return isWhite;}



private:
    QPoint position;
    ViewQLabel viewQLabel;
    bool isWhite{true};
};

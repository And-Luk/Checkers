#include "figure.h"

Figure::Figure(bool IsWhite, bool IsQueen, QPoint Position):isWhite{IsWhite},isQueen{IsQueen},position{Position}{}

void Figure::setIsWhite(bool IsWhite){isWhite=IsWhite;}
bool Figure::getIsWhite()const{return isWhite;}

void Figure::setIsQueen(bool IsQueen){isQueen=IsQueen;}
bool Figure::getIsQueen()const{return isQueen;}

void Figure::setIsFirstPlayr(bool IsFirstPlayr){isFirstPlayer=IsFirstPlayr;}
bool Figure::getIsFirstPlayr()const{return isFirstPlayer;}

void Figure::setPosition(QPoint Position){position= Position;}
QPoint Figure::getPosition()const{return position;}

void Figure::setIsBlokedState(bool IsBlokedState){isBlokedState= IsBlokedState;}
bool Figure::getIsBlokedState()const{return isBlokedState;}

void Figure::setVPathway(QVector<Pathway> VPathway){vPathway<< VPathway;}
void Figure::setVPathway(Pathway pathway){vPathway<< pathway;}
QVector<Pathway> Figure::getVPathway()const {return  vPathway;}


Figure::~Figure(){}

QPoint pointFromVPathway(QVector <Pathway> vPathway){
    if (!vPathway.empty()) {
        Pathway workPathway = vPathway.back();
        QPoint workPoint = workPathway.getPosition();
        return workPoint;
    }
    return QPoint(0,0);
}


void Figure::clearPathway(){ if (!vPathway.empty()) { vPathway.clear(); }}


bool Figure::isItPossibleToBeat (QPoint Position, const Direction direction, const bool IsWhite, ViewLabel* doubArrayViewLabel[8][8])const{
    #define notEmptyNextCell(x,y) doubArrayViewLabel[x][y] != nullptr
    #define    emptyNextCell(x,y) doubArrayViewLabel[x][y] == nullptr
    #define            alien(x,y) doubArrayViewLabel[x][y]->getIsWhite() != IsWhite

    #define  UpperLeft  (x>1)&&(y>1)
    #define  UpperRight (x<6)&&(y>1)
    #define  DownLeft   (x>1)&&(y<6)
    #define  DownRight  (x<6)&&(y<6)

    int x = Position.x();
    int y = Position.y();

    bool nextCell=false;
    bool nextCellJump=false;

    switch (direction) {

    case Upper_Left:
       if (UpperLeft) {
           nextCell =  notEmptyNextCell(x-1,y-1);
           nextCellJump = emptyNextCell(x-2,y-2);
           if (nextCell && nextCellJump) {
               if (alien(x-1,y-1)) { return true; }
           }
       }
       break;

    case Upper_Right:
       if (UpperRight) {
           nextCell =  notEmptyNextCell(x+1,y-1);
           nextCellJump = emptyNextCell(x+2,y-2);
           if (nextCell && nextCellJump) {
               if (alien(x+1,y-1)) { return true; }
           }
       }
       break;

    case Down_Left:
       if (DownLeft) {
           nextCell =  notEmptyNextCell(x-1,y+1);
           nextCellJump = emptyNextCell(x-2,y+2);
           if (nextCell && nextCellJump) {
               if (alien(x-1,y+1)) { return true; }
           }
       }
       break;

    case Down_Right:
       if (DownRight) {
           nextCell =  notEmptyNextCell(x+1,y+1);
           nextCellJump = emptyNextCell(x+2,y+2);
           if (nextCell && nextCellJump) {
               if (alien(x+1,y+1)) { return true; }
           }
       }
       break;

   } // switch


   return false;
}


QVector<Pathway> Figure::pawnStep(ViewLabel*  doubArrayViewLabel[8][8])const{
    #define isEmptyNextCell(x,y) doubArrayViewLabel[x][y] == nullptr
    #define Upper_LeftPoint  QPoint(x-1,y-1)
    #define Upper_RightPoint QPoint(x+1,y-1)
    #define  Down_LeftPoint  QPoint(x-1,y+1)
    #define  Down_RightPoint QPoint(x+1,y+1)

    bool nextCell=false;
    QVector<Pathway> vPathway;
    int x = getPosition().x();
    int y = getPosition().y();
    if (getIsFirstPlayr()) {
        ///////////////////////////////  UPPER   ////////////////////////
        if ((x>0) && (y>0)) {
            nextCell = isEmptyNextCell(x-1,y-1);
            if (nextCell) {vPathway<<Pathway(Upper_LeftPoint); }
        }
        if ((x<7) && (y>0)) {
            nextCell = isEmptyNextCell(x+1,y-1);
            if (nextCell) {vPathway<<Pathway(Upper_RightPoint); }
        }
    }
    else {
        ///////////////////////////////  DOWN  //////////////////////////
        if ((x>0) && (y<7)) {
            nextCell = isEmptyNextCell(x-1,y+1);
            if (nextCell) {vPathway<<Pathway(Down_LeftPoint); }
        }
        if ((x<7) && (y<7)) {
            nextCell = isEmptyNextCell(x+1,y+1);
            if (nextCell) {vPathway<<Pathway(Down_RightPoint); }
        }
    }
    return vPathway;
}


QVector<Pathway> Figure::pawnBeats(QPoint Position, bool IsWhite, bool IsFirstPlayer, ViewLabel* doubArrayViewLabel[8][8])const{
#define notEmptyNextCell(x,y) doubArrayViewLabel[x][y] != nullptr
#define    emptyNextCell(x,y) doubArrayViewLabel[x][y] == nullptr
#define            alien(x,y) doubArrayViewLabel[x][y]->getIsWhite() != IsWhite

#define  UpperLeft  (x>1)&&(y>1)
#define  UpperRight (x<6)&&(y>1)
#define  DownLeft   (x>1)&&(y<6)
#define  DownRight  (x<6)&&(y<6)

#define Upper_LeftPoint  QPoint(x-1,y-1)
#define Upper_RightPoint QPoint(x+1,y-1)
#define  Down_LeftPoint  QPoint(x-1,y+1)
#define  Down_RightPoint QPoint(x+1,y+1)

#define Upper_LeftJump  QPoint(x-2,y-2)
#define Upper_RightJump QPoint(x+2,y-2)
#define  Down_LeftJump  QPoint(x-2,y+2)
#define  Down_RightJump QPoint(x+2,y+2)



    QVector<Pathway> vPathway;
    vPathway.clear();
    int x = Position.x();
    int y = Position.y();

    //не дальше зоны противника
    if ( IsFirstPlayer && y==0) {return vPathway;}
    if (!IsFirstPlayer && y==7) {return vPathway;}
    //

    bool nextCell=false;
    bool nextCellJump=false;
    ViewLabel* I_AM =doubArrayViewLabel[x][y];
    doubArrayViewLabel[x][y]=nullptr;              //<---------------&7777777777
    QVector<Direction> vDirection;
    vDirection<<Upper_Left<<Upper_Right<<Down_Left<<Down_Right;



    for (Direction direction : vDirection) {

        switch (direction) {
        case Upper_Left:
            if (UpperLeft) {
//                if (isItPossibleToBeat(Position,direction,IsWhite,doubArrayViewLabel)) {
//                    Pathway curentPathway = Pathway(Upper_LeftJump);
//                    curentPathway.setCount(1);
//                    curentPathway.setDownedPoints(Upper_LeftPoint);
//                    vPathway<<curentPathway;
//                }



                nextCell =  notEmptyNextCell(x-1,y-1);
                nextCellJump = emptyNextCell(x-2,y-2);
                if (nextCell && nextCellJump) {
                    if (alien(x-1,y-1)) {
                    Pathway curentPathway = Pathway(Upper_LeftJump);
                    curentPathway.setCount(1);
                    curentPathway.setDownedPoints(Upper_LeftPoint);
                    ViewLabel* copyViewLabel=doubArrayViewLabel[x-1][y-1];
                    doubArrayViewLabel[x-1][y-1]=nullptr;
                    QVector<Pathway> vAfterPathway;
                    vAfterPathway << pawnBeats(Upper_LeftJump, IsWhite, IsFirstPlayer, doubArrayViewLabel);
                    if (!vAfterPathway.empty()) {
                        for (Pathway pathway : vAfterPathway) {
                            vPathway<<pathway+curentPathway;
                            }
                        doubArrayViewLabel[x-1][y-1]=copyViewLabel;
                        break;

                    }
                    vPathway<<curentPathway;
                    doubArrayViewLabel[x-1][y-1]=copyViewLabel;
                    }
                }
            }
            break;

        case Upper_Right:
            if (UpperRight) {
//                if (isItPossibleToBeat(Position,direction,IsWhite,doubArrayViewLabel)) {
//                    Pathway curentPathway = Pathway(Upper_RightJump);
//                    curentPathway.setCount(1);
//                    curentPathway.setDownedPoints(Upper_RightPoint);
//                    vPathway<<curentPathway;
//                }








                nextCell =  notEmptyNextCell(x+1,y-1);
                nextCellJump = emptyNextCell(x+2,y-2);
                if (nextCell && nextCellJump) {
                    if (alien(x+1,y-1)) {
                    Pathway curentPathway = Pathway(Upper_RightJump);
                    curentPathway.setCount(1);
                    curentPathway.setDownedPoints(Upper_RightPoint);
                    ViewLabel* copyViewLabel=doubArrayViewLabel[x+1][y-1];
                    doubArrayViewLabel[x+1][y-1]=nullptr;
                    QVector<Pathway> vAfterPathway;
                    vAfterPathway << pawnBeats(Upper_RightJump, IsWhite, IsFirstPlayer, doubArrayViewLabel);
                    if (!vAfterPathway.empty() ) {
                        for (Pathway pathway : vAfterPathway) {
                            vPathway<<pathway+curentPathway;
                            }
                        doubArrayViewLabel[x+1][y-1]=copyViewLabel;
                        break;

                    }
                    vPathway<<curentPathway;
                    doubArrayViewLabel[x+1][y-1]=copyViewLabel;
                    }
                }
            }
            break;

        case Down_Left:
            if (DownLeft) {
//                if (isItPossibleToBeat(Position,direction,IsWhite,doubArrayViewLabel)) {
//                    Pathway curentPathway = Pathway(Down_LeftJump);
//                    curentPathway.setCount(1);
//                    curentPathway.setDownedPoints(Down_LeftPoint);
//                    vPathway<<curentPathway;
//                }







                nextCell =  notEmptyNextCell(x-1,y+1);
                nextCellJump = emptyNextCell(x-2,y+2);
                if (nextCell && nextCellJump) {
                    if (alien(x-1,y+1)) {
                    Pathway curentPathway = Pathway(Down_LeftJump);
                    curentPathway.setCount(1);
                    curentPathway.setDownedPoints(Down_LeftPoint);
                    ViewLabel* copyViewLabel=doubArrayViewLabel[x-1][y+1];
                    doubArrayViewLabel[x-1][y+1]=nullptr;
                    QVector<Pathway> vAfterPathway;
                    vAfterPathway << pawnBeats(Down_LeftJump, IsWhite, !IsFirstPlayer, doubArrayViewLabel);
                    if (!vAfterPathway.empty()) {
                        for (Pathway pathway : vAfterPathway) {
                            vPathway<<pathway+curentPathway;
                            }
                        doubArrayViewLabel[x-1][y+1]=copyViewLabel;
                        break;

                    }
                    vPathway<<curentPathway;
                    doubArrayViewLabel[x-1][y+1]=copyViewLabel;
                    }
                }
            }
            break;

        case Down_Right:
            if (DownRight) {
//                if (isItPossibleToBeat(Position,direction,IsWhite,doubArrayViewLabel)) {
//                    Pathway curentPathway = Pathway(Down_RightJump);
//                    curentPathway.setCount(1);
//                    curentPathway.setDownedPoints(Down_RightPoint);
//                    vPathway<<curentPathway;
//                    }






                //nextCell =  notEmptyNextCell(x+1,y+1);
                //nextCellJump = emptyNextCell(x+2,y+2);
                //if (nextCell && nextCellJump) {
                    if (isItPossibleToBeat(Position,direction,IsWhite,doubArrayViewLabel)) {   //alien(x+1,y+1)
                    Pathway curentPathway = Pathway(Down_RightJump);
                    curentPathway.setCount(1);
                    curentPathway.setDownedPoints(Down_RightPoint);
                    ViewLabel* copyViewLabel=doubArrayViewLabel[x+1][y+1];
                    doubArrayViewLabel[x+1][y+1]=nullptr;
                    QVector<Pathway> vAfterPathway;
                    vAfterPathway << pawnBeats(Down_RightJump, IsWhite, !IsFirstPlayer, doubArrayViewLabel);
                    if (!vAfterPathway.empty()) {
                        for (Pathway pathway : vAfterPathway) {
                            vPathway<<pathway+curentPathway;
                            }
                        doubArrayViewLabel[x+1][y+1]=copyViewLabel;
                        break;

                    }
                    vPathway<<curentPathway;
                    doubArrayViewLabel[x+1][y+1]=copyViewLabel;
                    }
                //}
            }
            break;


        }
    }//for

    doubArrayViewLabel[x][y]=I_AM;
    return vPathway;
}


QVector<Pathway> Figure::emptyWay(QPoint Position, const Direction direction, ViewLabel* doubArrayViewLabel[8][8])const{
#define isEmptyNextCell(x,y) doubArrayViewLabel[x][y] == nullptr
#define Upper_LeftPoint  QPoint(x-1,y-1)
#define Upper_RightPoint QPoint(x+1,y-1)
#define  Down_LeftPoint  QPoint(x-1,y+1)
#define  Down_RightPoint QPoint(x+1,y+1)

#define  _UpperLeft  (x>0)&&(y>0)
#define  _UpperRight (x<7)&&(y>0)
#define  _DownLeft   (x>0)&&(y<7)
#define  _DownRight  (x<7)&&(y<7)


    bool nextCell=false;
    QVector<Pathway> vPathway;
    vPathway.clear();                     ///?????????????????

    QVector<Pathway> vPathwayAfter;
    int x = Position.x();
    int y = Position.y();

    switch (direction) {

    case Upper_Left:
        if (_UpperLeft) {
            nextCell = isEmptyNextCell(x-1,y-1);
            if (nextCell) {
                Pathway pathway(Upper_LeftPoint);
                pathway.setDirection(direction);
                vPathway<<pathway;
                vPathwayAfter<<emptyWay(Upper_LeftPoint, direction, doubArrayViewLabel);
                if (!vPathwayAfter.empty()) {
                    vPathway<<vPathwayAfter;
                }
            }
        }
        break;

    case Upper_Right:
        if (_UpperRight) {
            nextCell = isEmptyNextCell(x+1,y-1);
            if (nextCell) {
                Pathway pathway(Upper_RightPoint);
                pathway.setDirection(direction);
                vPathway<<pathway;
                vPathwayAfter<<emptyWay(Upper_RightPoint, direction, doubArrayViewLabel);
                if (!vPathwayAfter.empty()) {
                    vPathway<<vPathwayAfter;
                }
            }
        }
        break;

    case Down_Left:
        if (_DownLeft) {
            nextCell = isEmptyNextCell(x-1,y+1);
            if (nextCell) {
                Pathway pathway(Down_LeftPoint);
                pathway.setDirection(direction);
                vPathway<<pathway;
                vPathwayAfter<<emptyWay(Down_LeftPoint, direction, doubArrayViewLabel);
                if (!vPathwayAfter.empty()) {
                    vPathway<<vPathwayAfter;
                }
            }
        }
        break;

    case Down_Right:
        if (_DownRight) {
            nextCell = isEmptyNextCell(x+1,y+1);
            if (nextCell) {
                Pathway pathway(Down_RightPoint);
                pathway.setDirection(direction);
                vPathway<<pathway;
                vPathwayAfter<<emptyWay(Down_RightPoint, direction, doubArrayViewLabel);
                if (!vPathwayAfter.empty()) {
                    vPathway<<vPathwayAfter;
                }
            }
        }
        break;

    }

    return vPathway;
}


QVector<Pathway> Figure::emptyALLWay  (QPoint Position, ViewLabel* doubArrayViewLabel[8][8])const{
#define isEmptyNextCell(x,y) doubArrayViewLabel[x][y] == nullptr
#define Upper_LeftPoint  QPoint(x-1,y-1)
#define Upper_RightPoint QPoint(x+1,y-1)
#define  Down_LeftPoint  QPoint(x-1,y+1)
#define  Down_RightPoint QPoint(x+1,y+1)

#define  _UpperLeft  (x>0)&&(y>0)
#define  _UpperRight (x<7)&&(y>0)
#define  _DownLeft   (x>0)&&(y<7)
#define  _DownRight  (x<7)&&(y<7)

bool nextCell=false;
QVector<Pathway> vPathway;
QVector<Pathway> vPathwayDirection;
int x = getPosition().x();
int y = getPosition().y();


    ///////////////////////////////  UPPER   ////////////////////////
    if (_UpperLeft) {
        nextCell = isEmptyNextCell(x-1,y-1);
        if (nextCell) {
            vPathwayDirection<<emptyWay(Position, Upper_Left, doubArrayViewLabel);
            if (!vPathwayDirection.empty()) {
                vPathway<<vPathwayDirection;
                vPathwayDirection.clear();
            }
        }
    }

    if (_UpperRight) {
        nextCell = isEmptyNextCell(x+1,y-1);
        if (nextCell) {
            vPathwayDirection<<emptyWay(Position, Upper_Right, doubArrayViewLabel);
            if (!vPathwayDirection.empty()) {
                vPathway<<vPathwayDirection;
                vPathwayDirection.clear();
            }
        }
    }

    ///////////////////////////////  DOWN  //////////////////////////
    if (_DownLeft) {
        nextCell = isEmptyNextCell(x-1,y+1);
        if (nextCell) {
            vPathwayDirection<<emptyWay(Position, Down_Left, doubArrayViewLabel);
            if (!vPathwayDirection.empty()) {
                vPathway<<vPathwayDirection;
                vPathwayDirection.clear();
            }
        }
    }

    if (_DownRight) {
        nextCell = isEmptyNextCell(x+1,y+1);
        if (nextCell) {
            vPathwayDirection<<emptyWay(Position, Down_Right, doubArrayViewLabel);
            if (!vPathwayDirection.empty()) {
                vPathway<<vPathwayDirection;
                vPathwayDirection.clear();
            }

        }
    }

    //}
return vPathway;
}


QVector<Pathway> Figure::queenBeats(QPoint Position, const bool IsWhite, ViewLabel* doubArrayViewLabel[8][8])const{
    #define  UpperLeft  (x>1)&&(y>1)
    #define  UpperRight (x<6)&&(y>1)
    #define  DownLeft   (x>1)&&(y<6)
    #define  DownRight  (x<6)&&(y<6)

#define _queenBeats                                                     \
    vFirstEmptyPathway<<emptyWay(Position,direction,doubArrayViewLabel);\
    if (!vFirstEmptyPathway.empty()) {\
        workPoint = pointFromVPathway(vFirstEmptyPathway);\
        vFirstEmptyPathway.clear();\
    }\
    else {workPoint = Position;}\
    vPathway<<queenDirectionBeats(workPoint,direction,IsWhite,doubArrayViewLabel);\




    QVector<Pathway> vWorkPathway;
    QVector<Pathway> vFirstEmptyPathway;
    QVector<Pathway> vPathway;
    vPathway.clear();

    QPoint workPoint;

    int x = Position.x();
    int y = Position.y();

    QVector<Direction> vDirection;
    vDirection<<Upper_Left<<Upper_Right<<Down_Left<<Down_Right;

    for (Direction direction : vDirection) {

        switch (direction) {


        case Upper_Left:
            if (UpperLeft) { _queenBeats }
            break;

        case Upper_Right:
            if (UpperRight) { _queenBeats }
            break;

        case Down_Left:
            if (DownLeft) { _queenBeats }
            break;

        case Down_Right:
            if (DownRight) { _queenBeats }
            break;


        }

    }//for


    return vPathway;
}


QVector<Pathway> Figure::queenDirectionBeats (const QPoint Position, const Direction direction, const bool IsWhite, ViewLabel* doubArrayViewLabel[8][8])const{
    #define Upper_LeftPoint  QPoint(x-1,y-1)
    #define Upper_RightPoint QPoint(x+1,y-1)
    #define  Down_LeftPoint  QPoint(x-1,y+1)
    #define  Down_RightPoint QPoint(x+1,y+1)

    #define  UpperLeft  (x>1)&&(y>1)
    #define  UpperRight (x<6)&&(y>1)
    #define  DownLeft   (x>1)&&(y<6)
    #define  DownRight  (x<6)&&(y<6)

    int x = Position.x();
    int y = Position.y();

    QPoint workPoint;

    QVector<Pathway> vPathway;
    vPathway.clear();                       //?????????????????????

    QVector<Pathway> vPathwayBefore;
    QVector<Pathway> vPathwayAfter;
    QVector<Pathway> vPathwayModifier;

    //бъёт из точки предшедстующей сбиваемой фигуре

    switch (direction) {

    case Upper_Left:
        if (UpperLeft) {
            if (isItPossibleToBeat(Position,direction,IsWhite,doubArrayViewLabel)) {
                vPathwayBefore<<emptyWay(Upper_LeftPoint,direction,doubArrayViewLabel);
                for (Pathway pathway : vPathwayBefore) {
                    Pathway pathwayModifier = pathway;
                    pathwayModifier.setCount(1);
                    pathwayModifier.setDownedPoints(Upper_LeftPoint);
                    vPathwayModifier<<pathwayModifier;
                }
                vPathwayBefore.clear();
                vPathwayBefore<<vPathwayModifier;
                vPathwayModifier.clear();
                vPathway<<vPathwayBefore;
                workPoint = pointFromVPathway(vPathwayBefore);
                //first end
                // two start recursion
                if (isItPossibleToBeat(workPoint,direction,IsWhite,doubArrayViewLabel)){
                    vPathwayAfter<<queenDirectionBeats(workPoint,direction,IsWhite,doubArrayViewLabel);
                    if (!vPathwayAfter.empty()) {
                        for (Pathway pathway : vPathwayAfter) {
                            Pathway workPathway = vPathwayBefore.back();
                            Pathway pathwayModifier = pathway+workPathway;
                            vPathwayModifier<<pathwayModifier;
                        }
                        vPathway<<vPathwayModifier;
                        vPathwayModifier.clear();
                    }
                }
            }
        }
        break;

    case Upper_Right:
        if (UpperRight) {
            if (isItPossibleToBeat(Position,direction,IsWhite,doubArrayViewLabel)) {
                vPathwayBefore<<emptyWay(Upper_RightPoint,direction,doubArrayViewLabel);
                for (Pathway pathway : vPathwayBefore) {
                    Pathway pathwayModifier = pathway;
                    pathwayModifier.setCount(1);
                    pathwayModifier.setDownedPoints(Upper_RightPoint);
                    vPathwayModifier<<pathwayModifier;
                }
                vPathwayBefore.clear();
                vPathwayBefore<<vPathwayModifier;
                vPathwayModifier.clear();
                vPathway<<vPathwayBefore;
                workPoint = pointFromVPathway(vPathwayBefore);
                //first end
                // two start recursion
                if (isItPossibleToBeat(workPoint,direction,IsWhite,doubArrayViewLabel)){
                    vPathwayAfter<<queenDirectionBeats(workPoint,direction,IsWhite,doubArrayViewLabel);
                    if (!vPathwayAfter.empty()) {
                        for (Pathway pathway : vPathwayAfter) {
                            Pathway workPathway = vPathwayBefore.back();
                            Pathway pathwayModifier = pathway+workPathway;
                            vPathwayModifier<<pathwayModifier;
                        }
                        vPathway<<vPathwayModifier;
                        vPathwayModifier.clear();
                    }
                }
            }

        }
        break;

    case Down_Left:
        if (DownLeft) {
            if (isItPossibleToBeat(Position,direction,IsWhite,doubArrayViewLabel)) {
                vPathwayBefore<<emptyWay(Down_LeftPoint,direction,doubArrayViewLabel);
                for (Pathway pathway : vPathwayBefore) {
                    Pathway pathwayModifier = pathway;
                    pathwayModifier.setCount(1);
                    pathwayModifier.setDownedPoints(Down_LeftPoint);
                    vPathwayModifier<<pathwayModifier;
                }
                vPathwayBefore.clear();
                vPathwayBefore<<vPathwayModifier;
                vPathwayModifier.clear();
                vPathway<<vPathwayBefore;
                workPoint = pointFromVPathway(vPathwayBefore);
                //first end
                // two start recursion
                if (isItPossibleToBeat(workPoint,direction,IsWhite,doubArrayViewLabel)){
                    vPathwayAfter<<queenDirectionBeats(workPoint,direction,IsWhite,doubArrayViewLabel);
                    if (!vPathwayAfter.empty()) {
                        for (Pathway pathway : vPathwayAfter) {
                            Pathway workPathway = vPathwayBefore.back();
                            Pathway pathwayModifier = pathway+workPathway;
                            vPathwayModifier<<pathwayModifier;
                        }
                        vPathway<<vPathwayModifier;
                        vPathwayModifier.clear();
                    }
                }
            }
        }
        break;

    case Down_Right:
        if (DownRight) {
            if (isItPossibleToBeat(Position,direction,IsWhite,doubArrayViewLabel)) {
                vPathwayBefore<<emptyWay(Down_RightPoint,direction,doubArrayViewLabel);
                for (Pathway pathway : vPathwayBefore) {
                    Pathway pathwayModifier = pathway;
                    pathwayModifier.setCount(1);
                    pathwayModifier.setDownedPoints(Down_RightPoint);
                    vPathwayModifier<<pathwayModifier;
                }
                vPathwayBefore.clear();
                vPathwayBefore<<vPathwayModifier;
                vPathwayModifier.clear();
                vPathway<<vPathwayBefore;
                workPoint = pointFromVPathway(vPathwayBefore);
                //first end
                // two start recursion
                if (isItPossibleToBeat(workPoint,direction,IsWhite,doubArrayViewLabel)){
                    vPathwayAfter<<queenDirectionBeats(workPoint,direction,IsWhite,doubArrayViewLabel);
                    if (!vPathwayAfter.empty()) {
                        for (Pathway pathway : vPathwayAfter) {
                            Pathway workPathway = vPathwayBefore.back();
                            Pathway pathwayModifier = pathway+workPathway;
                            vPathwayModifier<<pathwayModifier;
                        }
                        vPathway<<vPathwayModifier;
                        vPathwayModifier.clear();
                    }
                }
            }
        }
        break;

    }

    return vPathway;
}







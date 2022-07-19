#include "creatorchild.h"

CreatorChild::CreatorChild(QWidget*  parentBoardLabel/*, Logic*  logic*/):Creator(parentBoardLabel/*, logic*/){
}




CreatorChild::~CreatorChild(){}



void CreatorChild::loadSnapshot(QVector<Figure*> &figures){ //    void loadSnapshot(QVector<Figure>);  // to Board

        QPixmap pix;
    foreach(Figure* figure, figures){
        if (figure->isWhite) {
            if (figure->isTheKing) {
                //pix load white kind
            }
            else {};//pix load white
        }
        if (!(figure->isWhite)) {
            if (figure->isTheKing) {
                //pix load black kind
            }
            else {};//pix load black
        }


        TimeLabel* pQL = Creator::create(figure->curentPosition,pix);
        figure->pQLabel=pQL;


        //figures.pop_front();
    }

}






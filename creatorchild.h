#pragma once

//#include<QObject>
#include<figure.h>
#include<creator.h>

//#include<logic.h>


//class Logic;
//class Creator;

#include <QObject>

class CreatorChild: public Creator{
    Q_OBJECT
public:
    //CreatorChild()= delete ;
    //explicit CreatorChild(QWidget* parentBoardLabel=nullptr, Logic* logic=nullptr);
    explicit CreatorChild(QWidget* parentBoardLabel=nullptr/*, Logic**/);
    //CreatorChild(QWidget* , Logic*);


    ~CreatorChild();
    void loadSnapshot(QVector<Figure*>&);  // to Board
    void moveFigure(QPoint,QPoint);
    void deleteFigure(QPoint);
    void loadFigurePictures(QPixmap*);

    Logic* logic{nullptr};

private:

    QPoint* arrayQPointTr[64];

//public slots:

//signals:
    //void messageQLabel(QPoint, QWidget*);
};


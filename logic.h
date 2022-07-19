#pragma once

#include<QObject>
#include<board.h>
#include<creator.h>

class Creator;


struct CreatorChild{
public:
    CreatorChild(QWidget* parentBoardLabel,QVector<QPixmap*> &vecQPix);
    ~CreatorChild();



    void loadSnapshot(QVector<FigureChild*>);  // to Board
    //void moveFigure(QPoint,QPoint);
    //void deleteFigure(QPoint);
    void loadFigurePictures(QPixmap*);
    Creator* creator{nullptr}; // (QWidget* parentBoardLabel, Logic* logic);
private:
    QVector<QPixmap*> vQPixmap;


};




class Logic:public QObject
{
    Q_OBJECT
public:
    Logic(QWidget* parentLabelBoard, QVector<QPixmap*> &vecQPixmap);
    ~Logic();

private:
    Board* boardLo{nullptr};
    QPoint startPosition{0,0};
    QWidget* parentLabelBoard{nullptr};
    CreatorChild* creatorChLo{nullptr};
    bool moveFigure(QPoint,QPoint);
    void deleteFigureChild(Pathway pathway);  //  QObject* timeLabel1, timeLabel2..., n
   // void deleteFigureChild(QObject*  timeLabel);  //QObject*
    //Pathway theBestChoice(QVector<Pathway> vPathway); // more downedFigures

    QVector<QPixmap*> vQPixmap;//{4};


public slots:
    void AskStatePosition(QObject*, bool, QPoint);
    void getBack();

signals:
    void EmitRequiredPosition(QObject*, QPoint);
    void deleteTimeLabel(QObject*);
};







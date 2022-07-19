#include "widget.h"

#include <QApplication>
#include<creator.h>
#include<board.h>
#include<manager.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    //-----------------------------------------------------------------
    QPixmap* boardCheckers  = new QPixmap;

    QPixmap whiteFigureChecker;
    QPixmap whiteFigureDame;
    QPixmap blackFigureChecker;
    QPixmap blackFigureDame;
    //-----------------------------------------------------------------
    boardCheckers->     load(":/new/prefix1/board");
    whiteFigureChecker. load(":/new/prefix1/whiteCh");
    whiteFigureDame.    load(":/new/prefix1/whiteQ");
    blackFigureChecker. load(":/new/prefix1/blackCh");
    blackFigureDame.    load(":/new/prefix1/blackQ");
    //-----------------------------------------------------------------
    QLabel* boardLabel= new QLabel(&w,0);
    boardLabel->setPixmap(*boardCheckers);
    boardLabel->setCursor(Qt::PointingHandCursor);
    boardLabel->setScaledContents(false);
    boardLabel->setAutoFillBackground(true);
    //-----------------------------------------------------------------
    QPixmap aQPixmap[4]{whiteFigureChecker,whiteFigureDame,blackFigureChecker,blackFigureDame};
    //-----------------------------------------------------------------

    Creator *creator = new Creator(boardLabel,aQPixmap);
    Board* boar = new Board(&w);
    Manager* manager = new Manager(&w);


    QObject::connect(creator,SIGNAL(signalRepeatMoveLabel(QPoint, QPoint)),manager,SLOT(slotRepeatMoveLabel(QPoint, QPoint)));

    QObject::connect(boar,SIGNAL(signalCreate(QVector<ViewLabel>)),creator,SLOT(slotCreate(QVector<ViewLabel>)));
    QObject::connect(boar,SIGNAL(signalMoveLabel(QPoint, QPoint)),creator,SLOT(slotMoveLabel(QPoint, QPoint)));
    QObject::connect(boar,SIGNAL(signalDeleteLabel(QVector<QPoint>)),creator,SLOT(slotDeleteLabel(QVector<QPoint>)));
    QObject::connect(boar,SIGNAL(signalChangeQLabel(ViewLabel)),creator,SLOT(slotChangeQLabel(ViewLabel)));
    QObject::connect(boar,SIGNAL(signalUnblockedPlayer(QVector<QPoint>)),creator,SLOT(slotUnblockedPlayer(QVector<QPoint>)));

    QObject::connect(manager,SIGNAL(signalViewFiguresOnBoard(bool)),boar,SLOT(slotViewFiguresOnBoard(bool)));
    QObject::connect(manager,SIGNAL(signalMakeFigures(unsigned int, unsigned int, unsigned int)),boar,SLOT(slotMakeFigures(unsigned int, unsigned int, unsigned int)));
    QObject::connect(manager,SIGNAL(signalUnblockedPlayer(short)),boar,SLOT(slotUnblockedPlayer(short)));
    QObject::connect(manager,SIGNAL(signalMoveLabel(QPoint, QPoint)),boar,SLOT(slotMoveLabel(QPoint, QPoint)));
    QObject::connect(manager,SIGNAL(signalWhoIsFirstPlaer(QString)),boar,SLOT(slotWhoIsFirstPlaer(QString)));

    //-----------------------------------------------------------------
    QHBoxLayout hlay;

    QPushButton qbt1("Run");
    QPushButton qbt2("Get Back");
    QPushButton qbt3("Save");
    QPushButton qbt4("Load");
    hlay.addWidget(&qbt1,0,Qt::AlignLeft);
    hlay.addWidget(&qbt2,1,Qt::AlignLeft);
    hlay.addWidget(&qbt3,1,Qt::AlignRight);
    hlay.addWidget(&qbt4,0,Qt::AlignRight);

    QObject::connect(&qbt1,SIGNAL(clicked()),manager,SLOT(slotRun()));


    QBoxLayout* lay  = new QBoxLayout(QBoxLayout::TopToBottom, &w);
    lay->setMargin(30);
    lay->addWidget(boardLabel); //Qt::TopLeftSection
    lay->addLayout(&hlay,0);

    w.setFixedSize(lay->sizeHint());
    w.setLayout(lay);
    w.move(50,50);

    w.show();
    return a.exec();
}

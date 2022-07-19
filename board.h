#pragma once

#include <QObject>
#include<pawn.h>
#include<queen.h>


class Board : public QObject
{
    Q_OBJECT
public:
    explicit Board(QObject *parent = nullptr);
    ~Board();

    //void calculateField();

    QVector<Figure*> getSnapshot(); // for CreatorChild
    QVector<Figure*> snapshot;

    void setSnapshot();
    void moveInDoubleArray(QPoint startPosition, QPoint curentPosition);

    void serializationCurentSnapshot();
    void getBack();

    void loadFiguresOnBoard(); //load Figures On Board
    void MoveLabel(QPoint position, QPoint newPosition);

signals:
    void signalCreate(const QVector<ViewLabel> vViewLabel);
    void signalMoveLabel(QPoint position, QPoint newPosition);
    void signalDeleteLabel(QVector<QPoint> const vQPoint);
    void signalChangeQLabel(const ViewLabel viewLabel);
    void signalUnblockedPlayer(QVector<QPoint> vUnblocked);
    void signalBlockedAllLabel();

public slots:
    void slotViewFiguresOnBoard(bool ViewHide);
    void slotMakeFigures(unsigned int Where, unsigned int Color, unsigned int Who);
    void slotUnblockedPlayer(const short first_or_second);
    void slotMoveLabel(QPoint position, QPoint newPosition);
    void slotWhoIsFirstPlaer(QString Color);
    void slotReplaceFigure(Figure* I_AM);

private:
    QVector<Figure*> vPFigure;
    Figure* doubArrayPFigure[8][8]{{nullptr}};
    void deleteFigures(QVector<QPoint> vQPoint);
    void deleteFigure(Figure* Figure);
    void deleteFigure(QPoint Position);

    unsigned int wherePosition;
    unsigned int colorFigure;
    unsigned int whoFigure;
    short first_or_second{1};

    QPoint arrayPositionTrue[32];
    //QVector<Pathway> pawn(Figure* doubArrayPFigure[8][8]  , Figure* pFigureChild)const;
    //QVector<Pathway> pawnOneStep(Figure* doubArrayPFigure[8][8]  , Figure* )const;
    //QVector<Pathway> queen(Figure* doubArrayPFigure[8][8]  , Figure* )const;

    void makeFiguresWithSnapshot(unsigned int Where, unsigned int Color, unsigned int Who);
    void serializationField();
    void calculate()const;
    void nextPlayerUnblocked();
    void loadFigureOnBoard(Figure* figure);
};

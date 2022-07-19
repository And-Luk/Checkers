#pragma once

#include <QObject>
#include<QPoint>

class Manager : public QObject
{
    Q_OBJECT
public:
    explicit Manager(QObject *parent = nullptr);
    void MakeFigures(unsigned int Where, unsigned int Color, unsigned int Who);

public slots:
    //void slotMoveLabel(QPoint position, QPoint newPosition);
    void slotRun();
    void slotRepeatMoveLabel(QPoint position, QPoint newPosition);
    //signalMoveLabel(QPoint position, QPoint newPosition);

signals:
    void signalViewFiguresOnBoard(bool ViewHide);
    void signalMakeFigures(unsigned int Where, unsigned int Color, unsigned int Who);
    void signalUnblockedPlayer(short first_or_second);
    void signalMoveLabel(QPoint position, QPoint newPosition);
    void signalWhoIsFirstPlaer(QString white_or_black);
    //void slotViewFiguresOnBoard(bool)
    //void slotMakeFigures(unsigned int, unsigned int, unsigned int)


};


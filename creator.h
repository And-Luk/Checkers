#pragma once

#include <QObject>
#include<label.h>
#include<pathway.h>
#include<realcoordinates.h>
#include<ViewLabel.h>

//class ERROR;


class Creator : public QObject
{
    Q_OBJECT
public:
    explicit Creator(QWidget *parentQLabelBoard = nullptr, QPixmap *arrQPixmap = nullptr);
    Creator()= delete;
    ~Creator();

public slots:
     void slotCreate(QVector<ViewLabel> const vViewLabel);
     void slotMoveLabel(QPoint position, QPoint newPosition);
     void slotDeleteLabel(QVector<QPoint> const vQPoint);
     void slotChangeQLabel(const ViewLabel viewLabel);
     void slotRepeatMoveLabel(QPoint position, QPoint newPosition);
     void slotUnblockedPlayer(QVector<QPoint> vUnblocked);
     void slotBlockedAllLabel();

private:
     QWidget* parentQLabel;
     QPixmap aQPixmap[4];
     RealCoordinates* realCoordinates{nullptr};
     QVector<Label*> vLabel/*{24}*/;
     void create(const ViewLabel viewLabel);
     //void create(const ViewLabel viewLabel);
     void deleteLabel(const QPoint  Position);


signals:
     void signalRepeatMoveLabel(QPoint position, QPoint newPosition);
     //void signalMoveLabel(QPoint position, QPoint newPosition);
};




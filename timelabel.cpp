#include "timelabel.h"


TimeLabel::TimeLabel(  QWidget* pqwd): QLabel(pqwd),pqwdTr{pqwd} {
    //this->setWindowFlag(Qt::WindowStaysOnBottomHint, true);
    //this->setWindowFlag(Qt::WindowStaysOnTopHint);
    //setWindowFlag(F,true);
}


void TimeLabel::mouseMoveEvent(QMouseEvent *ev){
    this->move(mapToParent(ev->pos()-DragPoint));
    }


void TimeLabel::mousePressEvent(QMouseEvent *ev){

    setCursor(Qt::DragMoveCursor);
    DragPoint = ev->pos();
    QPoint currentPoint = mapToParent( ev->pos()-DragPoint);
    emit TellPosition(true, currentPoint);
    //this->setWindowFlag(Qt::WindowStaysOnTopHint, true );
    //this->setWindowFlag(Qt::WindowStaysOnBottomHint);
    }


void TimeLabel::mouseReleaseEvent(QMouseEvent *ev){
    QPoint currentPoint = mapToParent( ev->pos()-DragPoint);
    setCursor(Qt::OpenHandCursor);
    emit TellPosition(false, currentPoint);
}



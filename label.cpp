#include "label.h"

Label::Label(QWidget* parentQLabel):QLabel(parentQLabel)
{
    setWindowFlag(Qt::WindowStaysOnBottomHint, true);

    setMouseTracking(true);

}


void Label::setPosition(QPoint const Position){position = Position;}


QPoint Label::getPosition()const{return position;}


void Label::setLockedState(bool state){lockedState = state;}


void Label::mousePressEvent(QMouseEvent *ev){
    if (!lockedState) {
        setMouseTracking(false);
        bottonPress=true;
        setCursor(Qt::DragMoveCursor);
        DragPoint = ev->pos();
    }
}


void Label::mouseMoveEvent(QMouseEvent *ev){
    if (!lockedState) {
        setCursor(Qt::OpenHandCursor);
    }
    if (!lockedState && bottonPress) {
        setCursor(Qt::DragMoveCursor);
        setMouseTracking(false);
        this->move(mapToParent(ev->pos()-DragPoint));
    }
}


void Label::mouseReleaseEvent(QMouseEvent *ev){
    if (!lockedState) {
        //lockedState=true;
        bottonPress=false;
        setMouseTracking(true);

        QPoint newPosition = mapToParent( ev->pos()-DragPoint);
        setCursor(Qt::PointingHandCursor);
        emit signalMoveLabel(position, newPosition);
    }
}


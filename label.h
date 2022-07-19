#pragma once

#include<QtWidgets>
#include<QLabel>


class Label:public QLabel{
    Q_OBJECT
public:
    explicit Label(QWidget* parentQLabel=nullptr);
    void setLockedState(bool state);
    void setPosition(const QPoint Position);
    QPoint getPosition()const;

private:
    QPoint DragPoint;
    QPoint position;
    bool lockedState{true};
    bool bottonPress{false};

protected:
    //void contextMenuEvent(QContextMenuEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;

signals:
    void signalMoveLabel(QPoint position, QPoint newPosition);

};


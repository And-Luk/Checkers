#pragma once

#include<QtWidgets>
#include<QLabel>

class TimeLabel:public QLabel{
    Q_OBJECT
public:
    explicit TimeLabel(QWidget* pqwd=nullptr ); //, Qt::WindowFlags F=0

private:
    QWidget* pqwdTr{nullptr};

protected:
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    QPoint DragPoint;

signals:
    void TellPosition(bool, QPoint);

};

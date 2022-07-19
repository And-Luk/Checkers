#include "creator.h"

Creator::Creator(QWidget *parentQLabelBoard, QPixmap *arrQPixmap ): QObject(parentQLabelBoard), parentQLabel{parentQLabelBoard}
{
    for (int var = 0; var < 4; ++var) {
        aQPixmap[var]=arrQPixmap[var];
    }
    realCoordinates = new RealCoordinates(40,71);
}


Creator::~Creator(){
    if (!vLabel.empty()) {
        for (Label* label: vLabel) {
            if (label!=nullptr) {
                delete label;
            }
        }
    }
    delete realCoordinates;
}


void Creator::create(ViewLabel const viewLabel){
    Label* pViewLabel = new Label(parentQLabel);
    pViewLabel->setPosition(viewLabel.getPosition());
    switch (viewLabel.getViewQLabel()) {
    case whiteCh: pViewLabel->setPixmap(aQPixmap[0]);  break;
    case whiteQ:  pViewLabel->setPixmap(aQPixmap[1]);  break;
    case blackCh: pViewLabel->setPixmap(aQPixmap[2]);  break;
    case blackQ:  pViewLabel->setPixmap(aQPixmap[3]);  break;
    default: /*throw ERROR;*/       break;
    }
    QPoint realPoint = realCoordinates->virtualToReal(viewLabel.getPosition());
    pViewLabel->move(realPoint);
    vLabel.push_back(pViewLabel);
    pViewLabel->show();
    QObject::connect(pViewLabel,SIGNAL(signalMoveLabel(QPoint , QPoint )),SLOT(slotRepeatMoveLabel(QPoint , QPoint )));

}


void Creator::deleteLabel(QPoint const position){
    int count=0;
    for (Label* label : vLabel) {
        if (position==label->getPosition()) {
            delete label;
            vLabel.remove(count);
            //vLabel.pop_back();
            break;

        }
        count++;
    }

    //delete vLabel[count];

    //vLabel.removeAt(count);
    //vLabel.remove(count);
}


void Creator::slotMoveLabel(QPoint position, QPoint newPosition){
    short count=0;
    QPoint realNewPosition;
    Label* labelForTime;
    for (Label* label: vLabel) {
        if (label->getPosition()==position) {
            labelForTime=label;
            realNewPosition = realCoordinates->virtualToReal(newPosition);
            //label->move(realNewPosition);
            //label->setPosition(newPosition);
            break;
        }
        count++;
    }
    labelForTime->move(realNewPosition);
    labelForTime->setPosition(newPosition);
    //ViewLabel viewLabel;
    //if (vLabel[count]->) {}


}


void Creator::slotCreate(QVector<ViewLabel> const vViewLabel){
    for (ViewLabel viewLabel : vViewLabel) {
        create(viewLabel);
    }
}


void Creator::slotRepeatMoveLabel(QPoint position, QPoint newPosition){
    QPoint newVirtualPosition = realCoordinates->realToVirtual(newPosition);
    //emit signalMoveLabel(position,  newVirtualPosition);
    emit signalRepeatMoveLabel(position, newVirtualPosition);
}


void Creator::slotDeleteLabel(QVector<QPoint> const vQPoint){
    for (QPoint position : vQPoint) {
        deleteLabel(position);
    }
}


void Creator::slotChangeQLabel(const ViewLabel viewLabel){
    QPoint changeViewLabelPosition = viewLabel.getPosition();
    deleteLabel(changeViewLabelPosition);
    create(viewLabel);
}


void Creator::slotBlockedAllLabel(){
    for (Label* label: vLabel) { label->setLockedState(true); }
}


void Creator::slotUnblockedPlayer(QVector<QPoint> vUnblocked){
    if (vUnblocked.empty()) {slotBlockedAllLabel(); }
    for (QPoint point : vUnblocked) {
        for (Label* label: vLabel) {
            if (label->getPosition()==point) {
                label->setLockedState(false);
            }
        }
    }
//    for (Label* label: vLabel) {
//        //label->setLockedState(true);
//        if (vUnblocked.contains(label->getPosition())) {
//            label->setLockedState(false);
//        }
//    }
}
















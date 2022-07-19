#include "logic.h"

Logic::Logic(QWidget* parent, QVector<QPixmap*> &vecQPixmap ): parentLabelBoard{parent} {

    //QVector<QPixmap*> vQPixmap
    vQPixmap= vecQPixmap;//{4};
    unsigned int whereIsLocated = 267390960; // all figures 4294967295 // true work 4293922815  //267390960
    unsigned int    colorFigure = 267386880;  //4095  //true work 16773120                      //267386880
    unsigned int      whoFigure = 0;
    boardLo = new Board(whereIsLocated, colorFigure, whoFigure);  // create board & make figures with this position

    creatorChLo= new CreatorChild(parentLabelBoard, vecQPixmap); //Load PIXMAP board end all ches vecQPixmap
    creatorChLo->creator->toBindingLogic(this); // show Figures on board
    creatorChLo->loadSnapshot(boardLo->getSnapshot()); //make ALL FiguresChild to load map Figures

//set black figures to do is second player or.....
    foreach (FigureChild *pFigureChild, boardLo->getSnapshot()) {
        if (!(pFigureChild->getIsWhite())) {
            pFigureChild->setIsFirstPlayr(false);
        }
    }

    boardLo->calculateField();
///////////////////////////////////////////////////////////////////////////////////// TEST



///////////////////////////////////////////////////////////////////////////////////// TEST
    //moveFigure(QPoint(3,2),QPoint(4,3)); // work
}

/// доработать !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/// для прямого передвижения фигур из Logic
/// доработать !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool Logic::moveFigure(QPoint startPositiot, QPoint finishPosition){
    FigureChild* tempFigure = boardLo->operator()(startPositiot); // WORK!!!!!!!!!
    emit EmitRequiredPosition(tempFigure->pTimeLabel, finishPosition);
    return true;
}

void Logic::getBack(){
    //////////// nott nott
    ///


    for (int i=0;i<24;i++) {
        if (boardLo->arrayPFigure[i]!=nullptr) {
            TimeLabel* pTimeLabel =boardLo->arrayPFigure[i]->getPTimeLabel();
            QObject* pQObject_pTimeLabel = qobject_cast<QObject*>(pTimeLabel);
            emit deleteTimeLabel(pQObject_pTimeLabel); // //delete figure->pTimeLabel;
            boardLo->arrayPFigure[i]=nullptr;
        }


    }

    boardLo->getBack();
    creatorChLo->creator->~Creator();

    creatorChLo= new CreatorChild(parentLabelBoard, vQPixmap);
    creatorChLo->loadSnapshot(boardLo->getSnapshot()); //make ALL FiguresChild to load map Figures

    foreach (FigureChild *pFigureChild, boardLo->getSnapshot()) {
        if (!(pFigureChild->getIsWhite())) {
            pFigureChild->setIsFirstPlayr(false);
        }
    }

    boardLo->calculateField();


}



void Logic::deleteFigureChild(Pathway pathway){  //  QObject* timeLabel1, timeLabel2..., n
    QVector<Figure*> vPFigures;
    vPFigures<<pathway.getDownedFigures();

    for (Figure* pFigure: vPFigures) {

        if (pFigure!=nullptr) {

        QPoint downedQPoint = pFigure->curentPosition;
        int x = downedQPoint.x();
        int y = downedQPoint.y();

        for (int i=0;i<24;i++) {
            if (boardLo->arrayPFigure[i] == boardLo->doubArrayPFigure[x][y]) {
                boardLo->arrayPFigure[i]=nullptr;
                break;
            }
        }

        boardLo->doubArrayPFigure[x][y]=nullptr ;
        TimeLabel* pTimeLabel = pFigure->pTimeLabel;
        QObject* pQObject_pTimeLabel = qobject_cast<QObject*>(pTimeLabel);
        emit deleteTimeLabel(pQObject_pTimeLabel); // //delete figure->pTimeLabel;
        //boardLo->snapshot.clear();

        }
        //boardLo->snapshot.clear();

    }
    boardLo->snapshot.clear();
}



Logic::~Logic(){
    if (!boardLo) { delete boardLo; }
    if (!creatorChLo) { delete creatorChLo; }
}


bool contains(Pathway pathway, QPoint containsSomeCoordinate){
      if (pathway.getPos()==containsSomeCoordinate) { return true; }
      return false;
}


Pathway theBestChoice(QVector<Pathway> vPathway, QPoint containsSomeCoordinate){  // more downedFigures
     //if (vPathway.size()<1) { throw  Qt::WA_QuitOnClose; } // if ERROR
     if (vPathway.size()==1) { return vPathway.front(); }

     int count=0;
     int countBestPathway=0;
     int bestPosition=0;
     int value=0; //one *figureChild
     // может выбрать путь не предусмотренный юзером
     for (Pathway pathway : vPathway) {
         if (contains(pathway,containsSomeCoordinate)) {
             if (countBestPathway==0) { // first entry corresponds to
                 countBestPathway++;
                 value = pathway.getCount();
                 bestPosition=count;
             }
             if (pathway.getCount()>value) {
                 value = pathway.getCount();
                 bestPosition=count;}
         }
         count++;
     }
     return vPathway[bestPosition];
}





void Logic::AskStatePosition(QObject* tempQob, bool isStartPosition, QPoint curentPosition){
    //что делать с передвигаемой фигурой
    //посылает сигнал либо стартовой позиции либо новой
    //any other method Start
    //boardLo->operator()(curentPosition)->possiblePositions.contains(curentPosition);
    if (isStartPosition) {
        startPosition = curentPosition; //стартовая позиция Save
        return;
    }

    FigureChild* figureChild = boardLo->operator()(startPosition);
    QVector<Pathway> vPathway;
    vPathway<< figureChild->getPathway();
    //vPathway<< figureChild->;

    if (vPathway.size()==0) { // if no moves
        emit EmitRequiredPosition(tempQob,startPosition);
        return;
    }

    for (Pathway pathway : vPathway) {
        if (pathway.getCount()>0) {
            QPoint moveQPoint = theBestChoice(vPathway,curentPosition).getPos();
            if (moveQPoint==curentPosition) {
                Logic::deleteFigureChild(theBestChoice(vPathway,curentPosition));

                emit EmitRequiredPosition(tempQob,moveQPoint);
                boardLo->moveInDoubleArray(startPosition,curentPosition);
                boardLo->calculateField();
                boardLo->serializationCurentSnapshot();

                return;
            }
        }

        if (pathway.getPos()==curentPosition) {

            emit EmitRequiredPosition(tempQob,curentPosition);
            boardLo->moveInDoubleArray(startPosition,curentPosition);
            boardLo->calculateField();
            boardLo->serializationCurentSnapshot();

            return; //delete this here
        }
    }

    emit EmitRequiredPosition(tempQob,startPosition);

    //return;
}






//////////////////////////////////////////////////////////////////////////////////////////////////






//////////////////////////////////////////////////////////////////////////////////////////////////
//
//              CreatorChild
//
CreatorChild::CreatorChild(QWidget* parentBoardLabel, QVector<QPixmap*> &vecQPixmap):vQPixmap{vecQPixmap}{
    CreatorChild::creator = new Creator(parentBoardLabel);
}


CreatorChild::~CreatorChild(){
    if (!creator){ delete creator; }
}


void CreatorChild::loadSnapshot(QVector<FigureChild*>  vFiguresChild){ //    void loadSnapshot(QVector<Figure>);  // to Board

    for(FigureChild* figure: vFiguresChild){
        if (figure->isWhite) {//White Figure
            if (figure->isQueen) {figure->pTimeLabel=creator->create(figure->curentPosition,*vQPixmap[1]);}
            else {figure->pTimeLabel=creator->create(figure->curentPosition,*vQPixmap[0]);};
        }
        if (!(figure->isWhite)) {//Black Firure
            if (figure->isQueen) {figure->pTimeLabel=creator->create(figure->curentPosition,*vQPixmap[3]);}
            else {figure->pTimeLabel=creator->create(figure->curentPosition,*vQPixmap[2]);};
        }
    }
}













#include "board.h"
#include"smallFunction.cpp"

void makeArrayTruePosition(QPoint* arrayPositionTrue){
    //заполнить массив white square at board соответ разрешённых позиций
    int posAr=0;
    for (int y=0;y<8;y++) {
        if ((y%2) == 0) {
            for (int x=1;x<8;x+=2){
                arrayPositionTrue[posAr]=QPoint(x,y);
                posAr++;
            }
        }
        if ((y%2) == 1) {
            for (int x=0;x<8;x+=2) {
                arrayPositionTrue[posAr]=QPoint(x,y);
                posAr++;
            }
        }
    }
}


Board::Board(QObject *parent) : QObject(parent){
    makeArrayTruePosition(arrayPositionTrue);
}


Board::~Board(){
    if (!vPFigure.empty()) {
        for (Figure* figure : vPFigure) { delete figure; }
    }
}


void Board::makeFiguresWithSnapshot(unsigned int Where, unsigned int Color, unsigned int Who){
   // Clear the old game
    int sizeQVector = vPFigure.size();
   for (int i=0; i<sizeQVector; i++) {  deleteFigure(vPFigure.back());  }

   // Load The new Game
   int arrayPosition_iterator=0;
   for (int bit=0; bit<32; bit++) {
       if (test_bit(Where, bit)) {
           if (test_bit(Who, bit)) {
               vPFigure<< new Queen(test_bit(Color, bit), test_bit(Who, bit), arrayPositionTrue[arrayPosition_iterator]);
            }
            else {
                Pawn* pawn =new Pawn(test_bit(Color, bit), test_bit(Who, bit), arrayPositionTrue[arrayPosition_iterator]);
                QObject::connect(pawn,SIGNAL(signalReplaceFigure(Figure*)),SLOT(slotReplaceFigure(Figure*)));
                vPFigure<< pawn;
            }
      }
      arrayPosition_iterator++;
    }
    for (Figure* figure : vPFigure) {
        int x =figure->getPosition().x();
        int y =figure->getPosition().y();
        doubArrayPFigure[x][y]=figure;
    }
}


void Board::loadFiguresOnBoard(){
    QVector<ViewLabel> vViewLabel;
    for (Figure* figure: vPFigure) {
        if (figure->getIsWhite()) {
            if (figure->getIsQueen()) {
                vViewLabel<< ViewLabel(figure->getPosition(),whiteQ);
            }
            else {
                vViewLabel<< ViewLabel(figure->getPosition(),whiteCh);
            }
        }
        else {
            if (figure->getIsQueen()) {
                vViewLabel<< ViewLabel(figure->getPosition(),blackQ);
            }
            else {
                vViewLabel<< ViewLabel(figure->getPosition(),blackCh);
            }
        }
    }
    emit signalCreate(vViewLabel);
}


void Board::loadFigureOnBoard(Figure* figure){
    QVector<ViewLabel> vViewLabel;
    if (figure->getIsWhite()) {
        if (figure->getIsQueen()) {
            vViewLabel<< ViewLabel(figure->getPosition(),whiteQ);
        }
        else {
            vViewLabel<< ViewLabel(figure->getPosition(),whiteCh);
        }
    }
    else {
        if (figure->getIsQueen()) {
            vViewLabel<< ViewLabel(figure->getPosition(),blackQ);
        }
        else {
            vViewLabel<< ViewLabel(figure->getPosition(),blackCh);
        }
    }
    emit signalCreate(vViewLabel);
}


void Board::serializationField()
{
    wherePosition=0;
    colorFigure =0;
    whoFigure =0;
    QPoint position_QPoint;
    for (int bit=0; bit<32; bit++) {
        position_QPoint=arrayPositionTrue[bit];
        int x_coordinate = position_QPoint.x();
        int y_coordinate = position_QPoint.y();
        if (doubArrayPFigure[x_coordinate][y_coordinate]!=nullptr) {
            wherePosition = set_bit(wherePosition, bit);
            colorFigure = set_bit(colorFigure, bit, doubArrayPFigure[x_coordinate][y_coordinate]->getIsWhite());
            whoFigure = set_bit(whoFigure, bit, doubArrayPFigure[x_coordinate][y_coordinate]->getIsQueen());
        }
    }
}


void Board::calculate()const{
    ViewLabel* doubArrayViewLabel[8][8] = {{nullptr}};
    for (int x=0;x<8;x++) {
        for (int y=0;y<8;y++) {
            if (doubArrayPFigure[x][y]!=nullptr) {
                ViewLabel* adding = new ViewLabel();
                adding->setPosition(doubArrayPFigure[x][y]->getPosition());
                adding->setIsWhite(doubArrayPFigure[x][y]->getIsWhite());
                doubArrayViewLabel[x][y]= adding;
            }
        }
    }

    for (Figure* figure : vPFigure) {
        figure->calculate(doubArrayViewLabel);}
    for (int x=0;x<8;x++) {
        for (int y=0;y<8;y++) {
            delete doubArrayViewLabel[x][y];
        }
    }
}


void Board::slotWhoIsFirstPlaer(QString white_or_black){
    if (white_or_black == "black") {
        for (Figure* figure : vPFigure) {
            if (!figure->getIsWhite()) {figure->setIsFirstPlayr(true);}
            else{figure->setIsFirstPlayr(false);}
        }
    }
    if(white_or_black =="white"){
        for (Figure* figure : vPFigure) {
            if (figure->getIsWhite()) {figure->setIsFirstPlayr(true);}
            else{figure->setIsFirstPlayr(false);}
        }
    }
    calculate();
}


void Board::nextPlayerUnblocked(){
    QVector<QPoint> vFirstPlayr;
    QVector<QPoint> vSecondPlayr;   // SecondPlayr
    vFirstPlayr.clear();
    emit signalUnblockedPlayer(vFirstPlayr); //blocked ALL

    for (Figure* figure : vPFigure) {
        if (figure->getIsFirstPlayr()) {
            vFirstPlayr<<figure->getPosition();
        }
        else {vSecondPlayr<<figure->getPosition();}
    }

    if (first_or_second == 1) {
        emit signalUnblockedPlayer(vSecondPlayr);
        first_or_second=2;
        return;
    }
    if (first_or_second == 2) {
        emit signalUnblockedPlayer(vFirstPlayr);
        first_or_second=1;
    }
}


void Board::slotUnblockedPlayer(const short First_or_Second){
    first_or_second=First_or_Second;

    QVector<QPoint> vFirstPlayr;
    QVector<QPoint> vSecondPlayr;   // SecondPlayr
    vFirstPlayr.clear();
    emit signalUnblockedPlayer(vFirstPlayr); //blocked ALL

    for (Figure* figure : vPFigure) {
        if (figure->getIsFirstPlayr()) {
            vFirstPlayr<<figure->getPosition();
        }
        else {vSecondPlayr<<figure->getPosition();}
    }

    if (first_or_second == 1) {
        emit signalUnblockedPlayer(vFirstPlayr);
        return;
    }
    if (first_or_second == 2) {
        emit signalUnblockedPlayer(vSecondPlayr);
    }
}


void Board::slotMakeFigures(unsigned int Where, unsigned int Color, unsigned int Who){
    makeFiguresWithSnapshot(Where, Color, Who);
}


void Board::slotViewFiguresOnBoard(bool ViewHide){
    if (ViewHide) { loadFiguresOnBoard(); return;}
    else {
        QVector<QPoint> vQPoint;
        for (Figure* figure : vPFigure) {
            vQPoint<<figure->getPosition();
        }
        emit signalDeleteLabel(vQPoint);
    }
}


void Board::slotReplaceFigure(Figure* I_AM){
    QPoint position;
    Figure* queen;
    for (Figure* figure : vPFigure) {
        if (figure==I_AM) {
            position = I_AM->getPosition();
            queen = new Queen(I_AM->getIsWhite(), true, position);
            queen->setIsFirstPlayr(I_AM->getIsFirstPlayr());
            break;
        }
    }

    deleteFigure(I_AM);
    vPFigure<<queen;
    doubArrayPFigure[position.x()][position.y()] = queen;
    loadFigureOnBoard(queen);

    QVector<QPoint> vUnblocked;
    vUnblocked<<queen->getPosition();
    emit signalUnblockedPlayer(vUnblocked);
}


void Board::deleteFigure(Figure* pFigure){
    short count=0;
    QPoint position;
    for (Figure* figure: vPFigure) {
        if (figure==pFigure) {
            position=figure->getPosition();
            doubArrayPFigure[position.x()][position.y()]=nullptr;
            break;
        }
        count++;
    }
    QVector<QPoint> vQPoint;
    vQPoint<<vPFigure[count]->getPosition();

    delete  vPFigure[count];
    vPFigure.remove(count);
    emit signalDeleteLabel(vQPoint);
   // emit signalUnblockedPlayer(vQPoint);
}


Pathway* theBestChoice(QVector<Pathway> vPathway, QPoint newPosition){  // more downedFigures
     //if (vPathway.size()<1) { throw  Qt::WA_QuitOnClose; } // if ERROR
     //if (vPathway.size()==1) { return &vPathway.front(); }

     int count=0;
     bool atLeastOne{false};
     int countBestPathway=0;
     int bestPosition=0;
     int value=0; //one *figureChild
     // может выбрать путь не предусмотренный юзером по максимальному счётчику
     for (Pathway pathway : vPathway) {
         if (pathway.getPosition()==newPosition) {
             if (countBestPathway==0) { // for first entry corresponds to
                 countBestPathway++;
                 value = pathway.getCount();
                 bestPosition=count;
                 atLeastOne=true;
             }
             if (pathway.getCount()>value) {
                 value = pathway.getCount();
                 bestPosition=count;}
         }
         count++;
     }
     if (atLeastOne) {
         Pathway* pPathway = new Pathway(vPathway[bestPosition]);
         return pPathway;
     }
     return nullptr;
}


void Board::deleteFigure(QPoint Position){
    int figureIterator=0;
    for (Figure* figure : vPFigure) {
        if (figure->getPosition()==Position) {
            delete vPFigure[figureIterator];
            doubArrayPFigure[Position.x()][Position.y()]=nullptr;
            break;
            }
            figureIterator++;
        }
    vPFigure.remove(figureIterator);
    QVector<QPoint> vQPoint;
    vQPoint<<Position;
    emit signalDeleteLabel(vQPoint);
}


void Board::deleteFigures(QVector<QPoint> vQPoint){
    for (QPoint point : vQPoint) {
        deleteFigure(point);
    }
}


void Board::slotMoveLabel(QPoint position, QPoint newPosition){//посылает сигнал либо стартовой позиции либо новой позиции

    bool allows{false};
    for (int x=0;x<33;x++) {
        if (arrayPositionTrue[x]== newPosition) { allows=true; }
    }
    if (!allows) {emit signalMoveLabel(position, position); return; }






    for (Figure* figure : vPFigure) {//finde this figure in vPfigur and read her pathways
        QPoint figurePoint =figure->getPosition();//dellllllllllllll
        if (figurePoint==position) {
            QVector<Pathway> knockedDownFigures =figure->getVPathway();
            if(knockedDownFigures.size()<1) {emit signalMoveLabel(position, position); return;}
            if (knockedDownFigures[0].getCount()==0) { // фигура не бьёт
                for (Pathway pathway : knockedDownFigures) {
                    if (pathway.getPosition()==newPosition) {
                        //figure->setPosition(newPosition);
                        emit signalMoveLabel(position, newPosition);
                        doubArrayPFigure[newPosition.x()][newPosition.y()] = doubArrayPFigure[position.x()][position.y()];
                        doubArrayPFigure[position.x()][position.y()]=nullptr; //position.x()][position.y()
                        figure->setPosition(newPosition);
                        nextPlayerUnblocked();
                        calculate();
                        return;
                    }
                }
                emit signalMoveLabel(position, position);
                return; // фигура не бьёт //позиция не найдена
            }
            Pathway* bestChoice = theBestChoice(knockedDownFigures, newPosition);
            //figure->setPosition(newPosition);
            if (bestChoice!=nullptr) {
                QVector<QPoint> vKnockedDownFigures = bestChoice->getDownedPoints();
                emit signalMoveLabel(position, newPosition);
                doubArrayPFigure[newPosition.x()][newPosition.y()] = doubArrayPFigure[position.x()][position.y()];
                doubArrayPFigure[position.x()][position.y()]=nullptr;

                emit signalDeleteLabel(vKnockedDownFigures);
                deleteFigures(vKnockedDownFigures);
                figure->setPosition(newPosition);
                calculate();
                delete bestChoice;
                return;
            }

        }
    }
    emit signalMoveLabel(position, position);
}



















//////////////////////////////////////////////////////////////////////////////////////////////// END



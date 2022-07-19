#include "translatorarray.h"

TranslatorArray::TranslatorArray(int displacement,int step  )//QPoint** arrayQPoint):arrayQPointTr(arrayQPoint)
{
   // QPoint* arrayPoint[64]{nullptr};
    int z=0;
    for (int a=0;a<8;a++){
        for (int b=0;b<8;b++){
            arrayQPointTr[z] = new QPoint(displacement+(step*b),displacement+(step*a)); //(29+(57*b),29+(57*a))
            z++;
        }
    }
}


TranslatorArray::~TranslatorArray(){
    for (int z=0 ;z<64; z++)
        delete  arrayQPointTr[z];
}


QPoint TranslatorArray::translateFrom(QPoint point){
    //  преобразует реальные координаты в вида 138,258 241,342 итд
    //  возвращает точку из 64 элементного линейного масива реальных координат в пикселях
    // return *arrayQPointTr[((point.y())*8 + point.x())];
    int positionX = optimal_X_Position(arrayQPointTr, point,  0 ,  7);
    int positionY = optimal_Y_Position(arrayQPointTr, point, positionX,  0 ,  7);
    return QPoint(positionX,positionY);
}


QPoint TranslatorArray::translateBack(QPoint point){
    //  для сигнала из Logic преобразует координаты в вида 0,0 2,2 итд
    //  возвращает точку из 64 элементного линейного масива
    return *arrayQPointTr[((point.y())*8 + point.x())];
}


int TranslatorArray::optimal_X_Position(QPoint** const ArreyQPoint,const QPoint curentQPoint,
                                const int pointStart ,const int pointEnd){

    int pointMiddle= (pointEnd - pointStart)/2;
    int pointBefor =  pointStart + pointMiddle;
    int pointAfter =  pointBefor + 1;

    if ((pointEnd-pointStart)<2) {
        return  abs(ArreyQPoint[pointStart]->x()-curentQPoint.x())<
                abs(ArreyQPoint[pointEnd]->x()-curentQPoint.x())? pointStart: pointEnd;
    }


    if ((pointEnd-pointStart)<3) {
        if (abs(ArreyQPoint[pointEnd]->x()-curentQPoint.x())<
                abs(ArreyQPoint[pointBefor]->x()-curentQPoint.x())) {return pointEnd;}

     return optimal_X_Position(ArreyQPoint, curentQPoint,  pointStart ,  pointBefor);
    }



    if (abs(ArreyQPoint[pointBefor]->x()-curentQPoint.x())<
            abs(ArreyQPoint[pointAfter]->x()-curentQPoint.x())) {

     return optimal_X_Position(ArreyQPoint, curentQPoint,  pointStart ,  pointBefor );
    }

  return optimal_X_Position(ArreyQPoint, curentQPoint,  pointAfter ,  pointEnd);
}


int TranslatorArray::optimal_Y_Position(QPoint** const ArreyQPoint,const QPoint curentQPoint,const int positionX,
                                const int pointStart ,const int pointEnd){

    int pointMiddle= (pointEnd - pointStart)/2;
    int pointBefor =  pointStart + pointMiddle;
    int pointAfter =  pointBefor + 1;
    //int scale=positionX*8;

    if ((pointEnd-pointStart)<2) {
        return  abs(ArreyQPoint[pointStart*8+positionX]->y()-curentQPoint.y())<
                abs(ArreyQPoint[pointEnd*8+positionX]->y()-curentQPoint.y())? pointStart: pointEnd;
    }


    if ((pointEnd-pointStart)<3) {
        if (abs(ArreyQPoint[pointEnd*8+positionX]->y()-curentQPoint.y())<
                abs(ArreyQPoint[pointBefor*8+positionX]->y()-curentQPoint.y())) {return pointEnd;}

     return optimal_Y_Position(ArreyQPoint, curentQPoint,positionX,  pointStart ,  pointBefor);
    }



    if (abs(ArreyQPoint[pointBefor*8+positionX]->y()-curentQPoint.y())<
            abs(ArreyQPoint[pointAfter*8+positionX]->y()-curentQPoint.y())) {

     return optimal_Y_Position(ArreyQPoint, curentQPoint,positionX,  pointStart ,  pointBefor );
    }

  return optimal_Y_Position(ArreyQPoint, curentQPoint,positionX,  pointAfter ,  pointEnd);


}

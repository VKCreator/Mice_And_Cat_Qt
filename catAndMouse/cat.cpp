#include "cat.h"


Cat::Cat(int radius, QObject *parent)
    : QObject(parent), QGraphicsItem(), radiusHunter(radius), isStay(true), stop(false)
{
    runToMice = new QTimer(this);
    runToMice->setInterval(1000/10); // 2 секунды анимация
}

Cat::~Cat()
{
    // очищать память, выделенную в куче, для указателей не нужно, т.к передан родительский объект в конструктор
}

QRectF Cat::boundingRect() const
{
    /* возвращаем координаты расположения точки
     * по ним будет определяться нажатие точки
     * */
    return QRectF(-25,-25,50,50);
}

void Cat::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QString path = ":/cat.png"; // путь к изображению кота

    painter->drawPixmap(-25,-25,50,50, QPixmap(path));

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Cat::setRadiusHunter(int rad)
{
    radiusHunter = rad;
}

void Cat::attackOnTheMouse(qreal x, qreal y)
{
    QPointF pnt = this->scenePos(); // получении координат расположения кота

    coordMouseX = x;
    coordMouseY = y;

    lineBetweenCatAndMouse = new QLineF(pnt,QPointF(x,y)); // отрезок между котом и мышью

    // double distance = round(sqrt( pow(x - pnt.x(),2) + pow(y - pnt.y(),2) )); // вычисляем расстояние от центра кота до центра мыши
    double distance = round(lineBetweenCatAndMouse->length());

    qDebug() << QLineF(pnt,QPointF(x,y)).length();

    if (distance <= radiusHunter) // если радиус охоты больше или равен расстоянию между котом и мышью, то атакуем мышь
    {
        qDebug() << "съесть" << distance;
        isStay = false; // кот выходит на охоту
        emit catEats();
    }
    else
    {
        qDebug() << "не съесть" << distance;
        isStay = true; // кот сидит на месте
        emit catNotEats();
    }

}

void Cat::runToMouse()
{
   runToMice->start(); // запуск таймера анимации

}

void Cat::advance(int phase)
{
    if (phase)
        return;

    if (!isStay) // если кот охотится
    {
        if (stop)
        {
           this->setPos(this->pos() - lineBetweenCatAndMouse->pointAt( 1 / stepCat )); // поступательный возврат к центру

           if (QLineF(this->pos(), lineBetweenCatAndMouse->pointAt(0)).length() < 0.00001)
           {
               isStay = true; // сидеть на месте
               stop = false; // не у мыши, а в центре
               emit returnCenter(); // сигнал о возвращении в центр сцены
           }
        }
        else
        {
          this->setPos(this->pos() + lineBetweenCatAndMouse->pointAt( 1 / stepCat )); // движемся к мыши

          if (QLineF(this->pos(), lineBetweenCatAndMouse->pointAt(1)).length() < 0.00001)
          {
              stop = true; // сообщаем, что дошли до мыши
              emit skelet(); // съедаем её
          }
        }
    }
}

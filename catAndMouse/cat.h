#ifndef CAT_H
#define CAT_H


#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QSound>
#include <QTimer>
#include <QDebug>

class Cat: public QObject, public QGraphicsItem
{

    Q_OBJECT

public:

    explicit Cat(int radius, QObject *parent = 0);
    ~Cat();

signals:

    void catEats(); // сигнал испускается в том случае, если кот готов съесть мышь
    void catNotEats(); // сигнал испускается в том случае, если кот НЕ готов съесть мышь (мышь за радиусом охоты)
    void skelet(); // испускается, когда кот добирается до мыши и ест её
    void returnCenter(); // испускается, когда кот возвращается на центр сцены

public slots:

    void attackOnTheMouse(qreal, qreal); // слот для определения состояния кота - атака или нет
    void runToMouse(); // слот для запуска анимации - кот охотится за мышью

private:

    /* Данные методы виртуальные, поэтому их необходимо реализовать в случае наследования от QGraphicsItem */
    QRectF boundingRect() const override; // определение прямоугольной области объекта
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // установка изображения в прямоугольную область

    int radiusHunter; // радиус охоты кота
    int coordMouseX; // координата мыши
    int coordMouseY; // координата мыши
    bool isStay; // флаг для определения состояния кота - на месте, в центре или охотится
    double stepCat = 10;
    bool stop; // флаг для проверки - дошёл ли кот до мыши или нет
    QLineF* lineBetweenCatAndMouse;


public:

    void advance(int phase) override; // метод, который запускается во время перемещения сцены
    void setRadiusHunter(int rad); // функция для повторной установки радиуса охоты кота
    QTimer* runToMice; // таймер для анимации движения кота

};



#endif // CAT_H

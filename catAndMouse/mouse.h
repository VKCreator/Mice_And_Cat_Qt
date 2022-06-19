#ifndef MOUSE_H
#define MOUSE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QDebug>
#include <QTimer>
#include <QSound>

class Mouse: public QObject, public QGraphicsItem
{

    Q_OBJECT

public:
    explicit Mouse(QObject *parent = 0);
    ~Mouse();

    void advance(int phase) override; // метод, который запускается во время перемещения сцены
    void setDied(bool flag);
    QTimer *runaway; // таймер для перемещения мыши

signals:

    void changeX(); // испускается в том случае, если мышь переместилась


public slots:

    void mouseSit(); // мышь сидит на месте, скорость равна 0
    void mouseRunAway(); // мышь готовится убегать, скорость равна 20
    void setSkelet(); // установка картинки - черепа, если кот атаковал мышь


protected:
    /* Перегружаем методы нажатия мышью и отпускания клавиши мыши, для их перехвата */

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    /* Данные методы виртуальные, поэтому их необходимо реализовать в случае наследования от QGraphicsItem */

    QRectF boundingRect() const override; // определение прямоугольной области объекта
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // установка изображения в прямоугольную область

private:

    int xspeed; // скорость мыши
    bool pressed; // флаг нажатия на мышь
    bool isDied; // флаг для установления жива ли мышь
    QSound *soundMouse; // звук писка мыши

};


#endif

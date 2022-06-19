#include "mouse.h"


Mouse::Mouse(QObject *parent)
    : QObject(parent), QGraphicsItem()
{
    pressed = false; // по умолчанию мышь жива, скорость равна 0 и клика по мыши нет
    xspeed = 0;
    isDied = false;

    runaway = new QTimer(this); // выделяем память для таймера, родительским объектом является объект класса Mouse
    soundMouse = new QSound(":/04485.wav", this); // выделяем память для звука, родительским объектом является объект класса Mouse
    runaway->setInterval(1000/3); // устанавливаем интервал работы таймера, 3 кадра в секунду.

}

Mouse::~Mouse()
{
    // очищать память, выделенную в куче, для указателей не нужно, т.к передан родительский объект в конструктор
}

QRectF Mouse::boundingRect() const
{
    /* возвращаем координаты расположения точки по ним будет определяться нажатие точки */
    return QRectF(-25,-25,50,50);
}

void Mouse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QString path;

    if (isDied)
    {
           path = ":/premium-icon-skull.png";
    }
    else
    {
        if (this->pos().x() > 0)
        {
             path = ":/rat1Mirrorright.png"; // в зависимости от расположения мыши, устанавливаем изображение
        }
        else
        {
             path = ":/rat1.png";
        }

        if (pressed)
        {
              path = ":/rat2.png";
        }
    }


    painter->drawPixmap(-25,-25,50,50, QPixmap(path));

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Mouse::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    soundMouse->stop(); // как только отпускаем клавишу мыши, писк останавливается
    pressed = false;
    update(); // перерисовываем объект
}

void Mouse::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    soundMouse->play(); // запуск писка мыши при клике мышью
    pressed = true;
    update(); // перерисовка
}

void Mouse::setDied(bool flag)
{
    isDied = flag;
}

void Mouse::setSkelet()
{
    isDied = true; // мышь съели
    update(); // перерисовка
}

void Mouse::mouseSit()
{
    xspeed = 0; // кот готовится атаковать мышь, устанавливаем скорость = 0
}

void Mouse::mouseRunAway()
{
    xspeed = 20; // мышь готовится убегать, скорость = 20
    runaway->start(); // запускаем таймер анимации побега мыши.
}

void Mouse::advance(int phase)
{
    if (!isDied) // если мышь жива, то она двигается
    {
        if (!phase)
        { // фазы 0 и 1, оставим одну фазу, чтобы скорость не была в 2 раза выше
            if (this->pos().x() > 0)
            {
                  moveBy(xspeed,0);
            }
            else
            {
                  moveBy(-xspeed,0);
            }

           emit changeX(); // испускается сигнал о изменении положения мыши на сцене
        }
    }
}

#include "awardwidget.h"
#include "ui_awardwidget.h"

AwardWidget::AwardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AwardWidget)
{
    ui->setupUi(this); // устанавливаем в виджет пользовательский интерфейс

    awardSound = new QSound(":/7cf0c5055aa7b78.wav", this); // загружаем звук награды
}

AwardWidget::~AwardWidget()
{
    delete ui;
}

void AwardWidget::retranslate()
{
    QString miceRes = ui->labelRescue->text(); // сохраняем значения количества съеденных и спасшихся мышей
    QString miceEat = ui->labelEat->text();

    ui->retranslateUi(this); // переводим интерфейс

    ui->labelRescue->setText(miceRes); // восстанавливаем значения количества съеденных и спасшихся мышей после перевода
    ui->labelEat->setText(miceEat);
}

void AwardWidget::setCountStars(int countStars, int miceRescue, int miceEaten)
{
    // 1 звезда отображается всегда по умолчанию

    awardSound->play(); // запускаем звук победы

    QPixmap starsFull = QPixmap(":/free-icon-star-1828884.png");
    QPixmap starsEmpty = QPixmap(":/screenshot_4-removebg-preview.q4oFO.png");

    ui->labelst2->setPixmap(countStars >= 2 ? starsFull : starsEmpty); // устанавливаем в ярлыки звёзды
    ui->labelst3->setPixmap(countStars == 3 ? starsFull : starsEmpty);

    ui->labelRescue->setText(QString::number(miceRescue)); // устанавливаем количество съеденных и спасшихся мышей
    ui->labelEat->setText(QString::number(miceEaten));

}

void AwardWidget::on_pushButtonAgain_clicked()
{
    emit again(); // испускаем сигнал, означающий рестарт игры
}


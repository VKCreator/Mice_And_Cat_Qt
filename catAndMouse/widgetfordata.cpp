#include "widgetfordata.h"
#include "ui_widgetfordata.h"

WidgetForData::WidgetForData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetForData)
{
    ui->setupUi(this); // устанавливаем пользовательский интерфейс в виджет

    connect(ui->horizontalSliderCountMouse, SIGNAL(valueChanged(int)), ui->labelSlider, SLOT(setNum(int))); // соединяем слайдер и ярлык

    movie = new QMovie( ":/stormrun(1).gif"); // загружаем гиф-изображение
    ui->labelGifMouse->setMovie(movie); // устанавливаем в ярлык
    movie->start(); // запускаем

    ui->boxLengthOfSideScene->setMinimum(300); // определяем максимум и минимум длины стороны квадрата
    ui->boxLengthOfSideScene->setMaximum(500);

    startSettings(); // загружаем стартовые настройки
}

void WidgetForData::retranslate()
{
    QString labelSliderValue = ui->labelSlider->text();

    ui->retranslateUi(this); // вызываем функцию, которая реализована за программиста

    ui->labelRadiusCat->setText(QString(tr("Введите радиус охоты кота (0 - %1 ед.):")).arg(round((ui->boxLengthOfSideScene->value() * sqrt(2)) / 2)));
    ui->boxLengthOfSideScene->setSuffix(tr(" ед.")); // переводим суффиксы в спинбоксах
    ui->spinBoxRadius->setSuffix(tr(" ед."));

    ui->labelSlider->setText(labelSliderValue);

    ui->labelValueSide->setText(ui->boxLengthOfSideScene->text()); // возвращаем старые значения ярлыков
    ui->labelValueRadius->setText(ui->spinBoxRadius->text());
    ui->labelValueMouse->setText(QString::number(ui->horizontalSliderCountMouse->value())  + tr(" шт."));
}


void WidgetForData::updateData()
{

    ui->boxLengthOfSideScene->setEnabled(true); // восстанавливаем возможность изменять значения в спинбоксах и кликать по кнопкам
    ui->pushButtonSide->setEnabled(true);

    ui->spinBoxRadius->setEnabled(true);
    ui->pushButtonRadius->setEnabled(true);

    ui->pushButtonCountMouse->setEnabled(true);
    ui->horizontalSliderCountMouse->setEnabled(true);

    ui->labelSlider->setText(QString::number(ui->horizontalSliderCountMouse->value()));

    startSettings();
}

void WidgetForData::startSettings()
{
    ui->boxLengthOfSideScene->setSuffix(tr(" ед.")); // в спинбокс добавляем суффикс ед.

    this->setStyleSheet(""); // убираем серый фон

    ui->labelRadiusCat->setVisible(false); // скрываем виджеты
    ui->spinBoxRadius->setVisible(false);
    ui->pushButtonRadius->setVisible(false);

    ui->labelCountMouse->setVisible(false);
    ui->pushButtonCountMouse->setVisible(false);
    ui->horizontalSliderCountMouse->setVisible(false);
    ui->labelSlider->setVisible(false);

    ui->labelProgress->setVisible(false);
    ui->progressBar->setVisible(false);
    ui->progressBar->setValue(0);

    ui->labelValueMouse->setText("");
    ui->labelValueSide->setText("");
    ui->labelValueRadius->setText("");
}


WidgetForData::~WidgetForData()
{
    delete ui;
    delete movie;
}

void WidgetForData::on_pushButtonSide_clicked()
{

    ui->labelValueSide->setText(ui->boxLengthOfSideScene->text()); // устанавливаем снизу виджета полученное значение стороны квадрата

    ui->labelRadiusCat->setText(QString(tr("Введите радиус охоты кота (0 - %1 ед.):")).arg(round((ui->boxLengthOfSideScene->value() * sqrt(2)) / 2)));
    // пользуемся формулой описанной окружности вокруг квадрата, чтобы найти максимальное значение радиуса охоты в случае, если кот охотится по всей области появления мышей

    ui->spinBoxRadius->setMinimum(0);
    ui->spinBoxRadius->setMaximum(round((ui->boxLengthOfSideScene->value() * sqrt(2)) / 2));
    ui->spinBoxRadius->setSuffix(tr(" ед."));

    ui->boxLengthOfSideScene->setEnabled(false);
    ui->pushButtonSide->setEnabled(false);
    ui->labelRadiusCat->setVisible(true);
    ui->pushButtonRadius->setVisible(true);
    ui->spinBoxRadius->setVisible(true);
}

void WidgetForData::on_pushButtonRadius_clicked()
{
    ui->labelValueRadius->setText(ui->spinBoxRadius->text());
    ui->spinBoxRadius->setEnabled(false);
    ui->pushButtonRadius->setEnabled(false);

    ui->labelCountMouse->setVisible(true);
    ui->horizontalSliderCountMouse->setVisible(true);
    ui->pushButtonCountMouse->setVisible(true);
    ui->labelSlider->setVisible(true);

    ui->horizontalSliderCountMouse->setMinimum(1);
    ui->horizontalSliderCountMouse->setMaximum(50);
}

void WidgetForData::on_pushButtonCountMouse_clicked()
{

    ui->labelValueMouse->setText((QString::number(ui->horizontalSliderCountMouse->value()))  + tr(" шт."));
    ui->pushButtonCountMouse->setEnabled(false);
    ui->horizontalSliderCountMouse->setEnabled(false);

    ui->labelProgress->setVisible(true);
    ui->progressBar->setVisible(true);

    emit setProgressBar();
}

void WidgetForData::setValueProgressBar(int val)
{
    ui->progressBar->setValue(ui->progressBar->value() + val);

    if (ui->progressBar->value() == 100)
    {
        emit ready();
    }
}

int WidgetForData::getValueProgressBar()
{
    return ui->progressBar->value();
}

int WidgetForData::getSideScene()
{
    return ui->boxLengthOfSideScene->value();
}

int WidgetForData::getCountMouse()
{
    return ui->horizontalSliderCountMouse->value();
}

int WidgetForData::getRadiusCat()
{
    return ui->spinBoxRadius->value();
}



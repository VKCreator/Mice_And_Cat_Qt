#ifndef WIDGETFORDATA_H
#define WIDGETFORDATA_H

#include <QWidget>
#include <QMovie>
#include <QSpinBox>
#include <qDebug>
#include <QThread>

namespace Ui {
class WidgetForData;
}

class WidgetForData : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetForData(QWidget *parent = nullptr);
    ~WidgetForData();

signals:
    void setProgressBar();
    void ready();

private slots:

    void on_pushButtonSide_clicked();
    void on_pushButtonRadius_clicked();
    void on_pushButtonCountMouse_clicked();

public:

    void setValueProgressBar(int);

    int getValueProgressBar();
    int getSideScene();
    int getCountMouse();
    int getRadiusCat();

    void updateData();
    void retranslate();

private:
    Ui::WidgetForData *ui;
    QMovie *movie;

   void startSettings();
};

#endif // WIDGETFORDATA_H

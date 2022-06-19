#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <cstdlib>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QSpinBox>
#include <QComboBox>
#include <QTranslator>
#include <QWidgetAction>
#include "mouse.h"
#include "cat.h"
#include "widgetfordata.h"
#include "awardwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void newMouse();

private slots:

    void on_pushButtonReadySetGo_clicked();
    void installScene();
    void processingUsersData();
    void increaseProgressBar();
    void checkX();
    void setMouseOnScene();
    void removeSkelet();
    void updateCentralWidget();

protected:

    void changeEvent(QEvent * event) override;

private:

    void checkNumberOfMiceRemaining();

private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene;
    Mouse *mouse;
    Cat *cat;
    QGraphicsView * graphicsView;

    AwardWidget *widgetAward;
    WidgetForData * widgetData;
    QComboBox * comboBoxLanguage;
    QSound* backgroundSound;
    QTimer *tmr;

    QGraphicsRectItem *rect;
    QGraphicsEllipseItem *ellipseRadius;

    QTranslator qtLanguageTranslator;
    bool isFirstStart;

    int countMouse = 0;
    int sideScene = 0;
    int radiusCat = 0;

    int countMouseRunAway = 0;
    int CountMouseFood = 0;

};
#endif // MAINWINDOW_H

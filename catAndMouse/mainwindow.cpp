#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); // устанавливаем пользовательский интерфейс в главное окно
    this->setFixedSize(this->size()); // фиксируем размер окна по умолчанию

    backgroundSound = new QSound(":/449359103103a80.wav", this); // загружаем мелодию
    backgroundSound->setLoops(QSound::Infinite); // ставим на все время работы приложения
    backgroundSound->play(); // запускаем мелодию

    tmr = new QTimer(this); // таймер для прогресс-бара
    connect(tmr, SIGNAL(timeout()), this, SLOT(increaseProgressBar()));

    widgetData = new WidgetForData;
    widgetAward = new AwardWidget;

    comboBoxLanguage = new QComboBox(this);

    comboBoxLanguage->addItem(QIcon(":/russia_flag.png"), "Русский", QVariant("ru"));
    comboBoxLanguage->addItem(QIcon(":/united_kingdom_flag.png"), "English", QVariant("en_US")); // добавляем элементы в выпадающий список вместе с данными пользователя
    comboBoxLanguage->addItem(QIcon(":/germany_flag.png"), "Deutsch", QVariant("de"));
    comboBoxLanguage->addItem(QIcon(":/Flag_of_Tatarstan.svg.png"), "Татар", QVariant("tt"));
    comboBoxLanguage->addItem(QIcon(":/china_flag.png"), "中文", QVariant("zh"));

     connect(comboBoxLanguage, static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
             [this](const QString &str) {

         auto lang = comboBoxLanguage->itemData(comboBoxLanguage->currentIndex(), Qt::UserRole).toString();
 //        qDebug() << lang.toString();

//         qtLanguageTranslator.load(":/catAndMouse_" + lang);   // Загружаем перевод
         qDebug() << qtLanguageTranslator.load(":/catAndMouse_" + lang);
        // qtLanguageTranslator.load("helloUser_" + str,  QApplication::applicationDirPath() );   // Загружаем перевод

         qApp->installTranslator(&qtLanguageTranslator);        // Устанавливаем перевод в приложение
     }); // соединяем сигнал со слотом (лямбда-функция)

    ui->toolBar->addWidget(comboBoxLanguage);
    isFirstStart = true; // если первый запуск приложения


}

void MainWindow::changeEvent(QEvent *event)
{
    // В случае получения события изменения языка приложения
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
        widgetData->retranslate();
        widgetAward->retranslate();
    }
}


MainWindow::~MainWindow()
{
    delete ui;
//    delete scene;
//    delete tmr;
//    delete graphicsView;
//    delete backgroundSound;
    // очищать память, выделенную в куче, для указателей не нужно, т.к передан родительский объект в конструктор
}

void MainWindow::setMouseOnScene()
{
//   srand(time(NULL));

   mouse->setPos(-sideScene / 2 + 25 + rand() % (sideScene + 1 - 50), -sideScene / 2 + 25 + rand() % (sideScene + 1 - 50)); // устанавливаем координаты мыши
   mouse->setDied(false); // сообщаем, что появилась новая живая мышь
   mouse->update(); // обновляем изображение мыши
   mouse->show(); // показываем мышь на сцене

   cat->attackOnTheMouse(mouse->pos().x(), mouse->pos().y()); // запускаем функцию, которая обрабатывает положение мыши на сцене, от этого зависит действия кота
}

void MainWindow::removeSkelet()
{
    cat->runToMice->stop(); // останавливаем анимацию движения кота, кот в центре, значит, убираем останки мыши

    CountMouseFood++; // увеличиваем счетчик съеденных мышей
    countMouse--; // уменьшаем количество необработанных мышей

    mouse->hide(); // скрываем мышь по сцены

    checkNumberOfMiceRemaining(); // проверяем количество оставшихся мышей
}

void MainWindow::checkX()
{
    if (mouse->pos().x() <= -sideScene / 2 || mouse->pos().x() >= sideScene / 2) // если мыши вышла за пределы, то останавливаем таймер анимации
    {
        mouse->runaway->stop();

        countMouseRunAway++; // Увеличиваем счетчик спасшихся мышей
        countMouse--; // уменьшаем количество необработанных мышей

        mouse->hide(); // скрываем мышь по сцены

        checkNumberOfMiceRemaining(); // проверяем количество оставшихся мышей
    }
}

void MainWindow::checkNumberOfMiceRemaining()
{
    if (countMouse == 0) // подводим итоги
    {
//       ui->statusbar->showMessage(QString(tr("Съеденных мышей: %1, Спасшихся мышей: %2").arg(CountMouseFood).arg(countMouseRunAway)));

       graphicsView->setVisible(false); // скрываем представление сцены

       backgroundSound->stop(); // останавливаем основную мелодию игры


       int countStars = 0;

       if (countMouseRunAway < CountMouseFood)
       {
           countStars = 3;
       }
       else if (countMouseRunAway > CountMouseFood)
       {
           countStars = 1;
       }
       else
       {
           countStars = 2;
       }

       if (isFirstStart)
       {
              ui->verticalLayout->addWidget(widgetAward); // устанавливаем виджет итогов в вертикальный слой главного виджета
              connect(widgetAward, SIGNAL(again()), this, SLOT(updateCentralWidget()));
       }

       widgetAward->setVisible(true);
       widgetAward->setCountStars(countStars, countMouseRunAway, CountMouseFood); // ведём подсчёт количества звёзд

       isFirstStart = false; // следующая игра будет уже не первой
    }
    else
    {
       emit newMouse(); // запускаем новую мышь, если счетчик не равен 0
    }
}

void MainWindow::updateCentralWidget()
{
    widgetAward->setVisible(false);
    ui->centralwidget->setStyleSheet("background-color: rgb(211, 211, 211)");
    ui->toolBar->setVisible(true);
    ui->pushButtonReadySetGo->setVisible(true);
    ui->labelCatImage->setVisible(true);
    ui->labelGameHeader->setVisible(true);
    backgroundSound->play();

    CountMouseFood = 0;
    countMouseRunAway = 0;
}


void MainWindow::installScene()
{
    widgetData->setVisible(false);
   // delete widgetData; удаляем виджет с полученными данными

    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);
    outlinePen.setCapStyle(Qt::RoundCap);
    outlinePen.setJoinStyle(Qt::RoundJoin);

    if (isFirstStart)
    {
        graphicsView = new QGraphicsView(this); // создаем экземпляр графического представления
        scene = new QGraphicsScene(graphicsView); // создаем сцену

        graphicsView->setScene(scene); // устанавливаем сцену в представление графическое
        graphicsView->setBackgroundBrush(QPixmap(":/cheese.jpg")); // фон граф. представления

        scene->setItemIndexMethod(QGraphicsScene::NoIndex); // не индексируем объекты

        ui->verticalLayout->addWidget(graphicsView); // в слой центрального виджета устанавливаем графическое представление
        cat = new Cat(radiusCat, this); // создаем объект класса Cat
        scene->addItem(cat); // устанавливаем кота на сцену по центру

        connect(cat->runToMice, SIGNAL(timeout()), scene, SLOT(advance()));

        mouse = new Mouse(this); // создаем объект класса Mouse
        scene->addItem(mouse); // устанавливаем мышь на сцену

        connect(cat, SIGNAL(catEats()), mouse, SLOT(mouseSit())); // если кот будет есть мышь, то мышь сидит
        connect(cat, SIGNAL(catEats()), cat, SLOT(runToMouse())); // если кот будет есть мышь, то кот движется к мыши

        connect(cat, SIGNAL(catNotEats()), mouse, SLOT(mouseRunAway())); // если кот не будет есть мышь, то мышь убегает

        connect(mouse->runaway, SIGNAL(timeout()), scene, SLOT(advance())); // анимация побега мыши
        connect(mouse, SIGNAL(changeX()), this, SLOT(checkX())); // контроль выхода мыши за пределы сцены

        connect(cat, SIGNAL(skelet()), mouse, SLOT(setSkelet())); // если кот добрался до мыши, то вместо изобр. мыши появляется череп
        connect(cat, SIGNAL(returnCenter()), this, SLOT(removeSkelet())); // если кот вернулся в центр, то убираем скелет мыши

        connect(this, SIGNAL(newMouse()), this, SLOT(setMouseOnScene())); // если нужна новая мышь, то запускаем новую мышь на сцену
    }

    if (!isFirstStart)
    {
        scene->removeItem(rect);
        scene->removeItem(ellipseRadius);
    }

    scene->setSceneRect(-sideScene / 2, -sideScene / 2, sideScene, sideScene);  // устанавливаем размеры сцены
    rect = scene->addRect(scene->sceneRect(), outlinePen); // визуализируем границы сцены

    outlinePen.setColor(Qt::green);
    ellipseRadius = scene->addEllipse(QRectF(-radiusCat, -radiusCat, radiusCat*2, radiusCat*2 ), outlinePen); // визуализируем радиус охоты кота

    srand(time(NULL)); // рандомные числа

    tmr->stop(); // останавливаем таймер прогресс-бара

    cat->setRadiusHunter(radiusCat);
    cat->setPos(0,0);

    graphicsView->setVisible(true);

    emit newMouse(); // сигнализируем о том, что сцена готова к работе

}

void MainWindow::on_pushButtonReadySetGo_clicked()
{
    ui->pushButtonReadySetGo->setVisible(false);
    ui->labelCatImage->setVisible(false);
    ui->labelGameHeader->setVisible(false);

//    delete ui->pushButtonReadySetGo;
//    delete ui->labelCatImage;
//    delete ui->labelGameHeader;
//    delete ui->verticalLayout;

   // ui->toolBar->setVisible(false); // change !!!
    ui->centralwidget->setStyleSheet(""); // обнуляем стиль

    if (isFirstStart)
    {
//        widgetData = new WidgetForData(ui->centralwidget);
        ui->verticalLayout->addWidget(widgetData); // устанавливаем в слой центрального виджета виджет с полями для заполнения
        connect(widgetData, SIGNAL(setProgressBar()), this, SLOT(processingUsersData())); // если прогресс-бар установлен, то обрабатываются данные
        connect(widgetData, SIGNAL(ready()), this, SLOT(installScene())); // если данные собраны, то устанавливается сцена
    }
    else
    {
        widgetData->updateData();
        widgetData->setVisible(true);
    }
}

void MainWindow::processingUsersData()
{
    tmr->setInterval(2000); // за 2 секунды заполняется 25 процентов на прогресс-баре
    tmr->start();

    sideScene = widgetData->getSideScene(); // получаем данные
    countMouse = widgetData->getCountMouse();
    radiusCat = widgetData->getRadiusCat();
}

void MainWindow::increaseProgressBar()
{
     widgetData->setValueProgressBar(25); // заполнение прогресс-бара по таймеру
}



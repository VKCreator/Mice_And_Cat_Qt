#ifndef AWARDWIDGET_H
#define AWARDWIDGET_H

#include <QWidget>
#include <QSound>

namespace Ui {
class AwardWidget;
}

class AwardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AwardWidget(QWidget *parent = nullptr);
    ~AwardWidget();

signals:
    void again();

public slots:
    void setCountStars(int countStars, int miceRescue, int miceEaten);
    void retranslate();

private slots:
    void on_pushButtonAgain_clicked();

private:
    Ui::AwardWidget *ui;
    QSound *awardSound;
};

#endif // AWARDWIDGET_H

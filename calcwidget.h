#ifndef CALCWIDGET_H
#define CALCWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

class CalcWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CalcWidget(QWidget *parent = 0);

signals:

public slots:
private:
    QPushButton *calc;
    QLabel *result;

};

#endif // CALCWIDGET_H

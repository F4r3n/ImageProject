#ifndef CALCWIDGET_H
#define CALCWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QRect>
#include "labelimage.h"

class CalcWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CalcWidget(LabelImage *label);

signals:

public slots:
    void calculus();
private:
    QPushButton *calc;
    QLabel *result;
    QRect *rect;
    LabelImage *lab;

};

#endif // CALCWIDGET_H

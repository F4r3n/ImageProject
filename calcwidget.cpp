#include "calcwidget.h"

CalcWidget::CalcWidget(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *gr = new QGridLayout();
    setLayout(gr);
    calc = new QPushButton("Calcul");
    result = new QLabel("result");
    gr->addWidget(calc);
    gr->addWidget(result);
}

#ifndef PLOTINGWIDGET_H
#define PLOTINGWIDGET_H

#include <QDialog>
#include <QVector>
#include "qcustomplot.h"

class PlotingWidget : public QDialog
{

public:
    explicit PlotingWidget(QVector<double> x, QVector<double> y,QWidget *parent = 0 );



private:
    QCustomPlot *plot;
    QVector<double> x,y;

};

#endif // PLOTINGWIDGET_H

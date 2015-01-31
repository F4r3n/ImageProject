#ifndef PLOTINGWIDGET_H
#define PLOTINGWIDGET_H

#include <QDialog>
#include <QVector>
#include "qcustomplot.h"

class PlotingWidget : public QDialog
{

public:
    explicit PlotingWidget(QVector<double> x, QVector<double> y, QString name ="Plot" , QWidget *parent = 0 );
    double minValue(QVector<double> z);
    double maxValue(QVector<double> z);




private:
    QCustomPlot *plot;
    QVector<double> x,y;
    QPushButton *quit;

};

#endif // PLOTINGWIDGET_H

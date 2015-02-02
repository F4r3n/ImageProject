#ifndef PLOTINGWIDGET_H
#define PLOTINGWIDGET_H

#include <QDialog>
#include <QVector>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include "qcustomplot.h"

class PlotingWidget : public QDialog
{

public:
    explicit PlotingWidget(QVector<double> x, QVector<double> y, QString name ="Plot" , QWidget *parent = 0 );
    double minValue(const QVector<double> &z);
    double maxValue(const QVector<double> &z);
    int variation(const QVector<double> &z);
    double frequency(int v);


private:
    QCustomPlot *plot;
    QVector<double> x,y;
    QPushButton *quit;
    QLabel *info;

};

#endif // PLOTINGWIDGET_H

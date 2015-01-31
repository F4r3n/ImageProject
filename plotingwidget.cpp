#include "plotingwidget.h"

PlotingWidget::PlotingWidget(QVector<double> x, QVector<double> y , QWidget *parent) :
    QDialog(parent),x(x),y(y)
{
    resize(QSize(400,400));
    QGridLayout *gr = new QGridLayout();
    setLayout(gr);
    plot = new QCustomPlot();
    plot->setGeometry(0,0,400,400);
    plot->addGraph();
    plot->graph(0)->setData(x,y);
    plot->xAxis->setLabel("x");
    plot->yAxis->setLabel("y");
    gr->addWidget(plot);
    // set axes ranges, so we see all data:
    plot->xAxis->setRange(minValue(x), maxValue(y)+5);
    plot->yAxis->setRange(minValue(y)-5, maxValue(y)+5);
    plot->replot();
}


double PlotingWidget::minValue(QVector<double> z) {
    double min =1000;
    for(double i : z) {
        min =qMin(min,i);
    }
    return min;
}

double PlotingWidget::maxValue(QVector<double> z) {
    double max =0;
    for(double i : z) {
        max =qMax(max,i);
    }
    return max;
}


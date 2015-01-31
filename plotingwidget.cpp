#include "plotingwidget.h"

PlotingWidget::PlotingWidget(QVector<double> x, QVector<double> y , QWidget *parent) :
    QDialog(parent),x(x),y(y)
{
    plot = new QCustomPlot(this);
    plot->setGeometry(0,0,400,400);
    plot->addGraph();
    plot->graph(0)->setData(x,y);
    plot->xAxis->setLabel("x");
    plot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    plot->xAxis->setRange(0, 155);
    plot->yAxis->setRange(90, 100);
    plot->replot();
}

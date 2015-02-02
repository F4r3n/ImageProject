#include "plotingwidget.h"

PlotingWidget::PlotingWidget(QVector<double> x, QVector<double> y ,QString name, QWidget *parent) :
    QDialog(parent),x(x),y(y)
{
    setWindowTitle(name);
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
    plot->xAxis->setRange(0, maxValue(x)+5);
    plot->yAxis->setRange(minValue(y)-0.5, maxValue(y)+0.5);
    plot->replot();
    quit = new QPushButton("Quit");
    QString str;
    QTextStream i(&str);
    i << "Frequency " <<  frequency(variation(y));
    info = new QLabel(str);
    info->setMaximumHeight(30);
    gr->addWidget(info);

    gr->addWidget(quit);

    connect(quit,SIGNAL(clicked()),this,SLOT(close()));
}


double PlotingWidget::minValue(const QVector<double> &z) {
    double min =1000;
    qDebug() << z.size();
    for(double i : z) {
        qDebug()<< i;
        min =qMin(min,i);
    }
    return min;
}

double PlotingWidget::maxValue(const QVector<double> &z) {
    double max =0;
    for(double i : z) {
        max =qMax(max,i);
    }
    return max;
}

double PlotingWidget::frequency(int v) {
    int time = x.size()/15;
     return (v/2.f)*(1.f/time)*60.f;
}

int PlotingWidget::variation(const QVector<double> &z) {
    bool up = false;
    bool down = false;
    double max = maxValue(y);
    if(max<0.01) return 0;

    int i=0;
    for(double y : z) {
        if(y<0 && up == true) i++;
        if(y>0 && down == true) i++;

        if(y<0) {
            down =true;
            up = false;
        }
        if(y>0) {
            up =true;
            down = false;
        }

    }
    if(i>0) return i-1;
    return 0;
}


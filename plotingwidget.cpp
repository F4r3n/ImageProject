#include "plotingwidget.h"

#define PW_FS 15
#define PW_PMAX 200
#define PW_PMIN 5
#define PW_H 60

PlotingWidget::PlotingWidget(Vector<double> x, Vector<double> y , int n, QString name, QWidget *parent) :
    QDialog(parent),x(x),y(y)
{
    if(y.size()==0) return;
    setWindowTitle(name);
    resize(QSize(400,400));
    QGridLayout *gr = new QGridLayout();
    setLayout(gr);

    plot = new QCustomPlot();
    plot->setGeometry(0,0,400,400);
    plot->addGraph();
    plot->graph(nbGraph)->setData(x,y);
    plot->graph(nbGraph)->setPen(QPen(Qt::black));
    plot->xAxis->setLabel("x");
    plot->yAxis->setLabel("y");
    gr->addWidget(plot);
    plot->xAxis->setRange(0, n);

    double m = maxValue(y);
    double min = minValue(y);

    plot->yAxis->setRange(min,m);
    plot->replot();
    // plot->legend->setVisible(true);

    quit = new QPushButton("Quit");
    QString str;
    QTextStream i(&str);
    double v = variation(y)/4.f;
    qDebug() << "variation" << v*4;
    i << "Frequency " << frequencyTFD() << "\nNombre de variations (trigger) "
      << (v-1)*(60*15.f/x.size()) << "\n" << ((v+1) * 60*15.f/x.size());
    info = new QLabel(str);
    info->setMaximumHeight(60);
    gr->addWidget(info);
    gr->addWidget(quit);

    connect(quit,SIGNAL(clicked()),this,SLOT(close()));
}

void PlotingWidget::addGraph(Vector<double> x, Vector<double> y, QString name, QPen pen, bool rescale) {
    nbGraph++;
    plot->addGraph();
    plot->graph(nbGraph)->setData(x,y);
    plot->graph(nbGraph)->setPen(pen);
    plot->graph(nbGraph)->setName(name);
    plot->graph(nbGraph)->rescaleAxes(rescale);
}

double PlotingWidget::minValue(const Vector<double> &z) {
    double min =1000;
    for(double i : z) {
        min =qMin(min,i);
    }
    return min;
}

double PlotingWidget::maxValue(const Vector<double> &z) {
    double max =0;
    for(double i : z) {
        if(i>max) max=i;
    }
    return max;
}

double PlotingWidget::frequency(int v) {
    int time = x.size()/15;
    return (v/2.f)*(1.f/time)*60.f;
}

int PlotingWidget::variation(const Vector<double> &z) {
    bool up = false;
    bool down = false;
    double bande = 0.01;
    double max = maxValue(y);

    if(max<0.01) {
        return 0;
    }

    int i=0;
    int j=0;

    for(double y : z) {
        if(y<bande && up == true) {
            i++;
        }
        if(y>-bande && down == true) {
            i++;
        }
        if(y<bande) {

            down = true;
            up = false;
        }
        if(y>-bande) {
            up = true;
            down = false;
        }

        j++;
    }
    return i;
}

int PlotingWidget::maxX() {
    return (PW_PMAX/PW_H)*x.size()/PW_FS;
}

int PlotingWidget::minX() {
    return (PW_PMIN/PW_H)*x.size()/PW_FS;
}

double PlotingWidget::maximaLocal(int deb,int end) {
    double max = 0;
    int pos = 0;
    for(int i=deb;i<end;i++){

        if(max < y[i]) {
            max = y[i];
            pos = i;
        }
    }
    return pos;
}




double PlotingWidget::frequencyTFD() {
    int end = 150*x.size()/(PW_FS*PW_H);
    int deb = 50*x.size()/(PW_FS*PW_H);
    // int pos = 0;
    int pos = maximaLocal(deb,end);

    return (double)pos*PW_FS*PW_H/(double)x.size();

}


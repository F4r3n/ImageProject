#include "plotingwidget.h"

PlotingWidget::PlotingWidget(Vector<double> x, Vector<double> y ,QString name, QWidget *parent) :
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
    plot->xAxis->setRange(0, x.size()+5);
    plot->yAxis->setRange(minValue(y)-0.5, maxValue(y)+0.5);
    plot->replot();
    quit = new QPushButton("Quit");
    QString str;
    QTextStream i(&str);
    i << "Frequency " << frequencyTFD();
    info = new QLabel(str);
    info->setMaximumHeight(30);
    gr->addWidget(info);

    gr->addWidget(quit);

    connect(quit,SIGNAL(clicked()),this,SLOT(close()));
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

Vector<int> PlotingWidget::variation(const Vector<double> &z) {
    bool up = false;
    bool down = false;
    double max = maxValue(y);
    if(max<0.01) return 0;

    int i=0;
    int j=0;
    Vector<int> v;
    for(double y : z) {
        if(y<0 && up == true) {
            i++;
            v.push_back(j);
        }
        if(y>0 && down == true) {
            i++;
            v.push_back(j);

        }
        if(y<0) {
            down =true;
            up = false;
        }
        if(y>0) {
            up =true;
            down = false;
        }

        j++;
    }
    return v;
}

int PlotingWidget::maxX() {
    return (PMAX/H)*x.size()/FS;
}

int PlotingWidget::minX() {
    return (PMIN/H)*x.size()/FS;
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
    int end = maxX();
    int deb = minX();
   // int pos = 0;
   int pos = maximaLocal(deb,end);
    double max = y[pos];
    DerivedAlgo *d = new DerivedAlgo();
    Vector<int> v = variation(d->execute(x,y));

    for(int i : v) {
        qDebug() << y[i]/max;
       if( i>end) continue;
       if(fabs(y[i]/max)>0.5 && pos!=i) return -1;


    }
 return pos*FS*H/x.size();

}


#ifndef PLOTINGWIDGET_H
#define PLOTINGWIDGET_H

#include <QDialog>
#include <QVector>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QEvent>
#include "qcustomplot.h"
#include "Vector.h"
#include "derivedealgo.h"


class PlotingWidget : public QDialog
{

public:
    explicit PlotingWidget(Vector<double> x, Vector<double> y, QString name ="Plot" , QWidget *parent = 0 );
    double minValue(const Vector<double> &z);
    double maxValue(const Vector<double> &z);
    Vector<int> variation(const Vector<double> &z);
    double frequency(int v);
    int maxX();
    int minX();
    double maximaLocal(int deb, int end);
    double frequencyTFD();
	void addGraph(Vector<double> x, Vector<double> y, QString name, QPen pen, bool rescale);


private:
	short nbGraph = 0;
    QCustomPlot *plot;
    Vector<double> x,y;
    QPushButton *quit;
    QLabel *info;

};

#endif // PLOTINGWIDGET_H

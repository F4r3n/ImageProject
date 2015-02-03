#ifndef PLOTINGWIDGET_H
#define PLOTINGWIDGET_H

#include <QDialog>
#include <QVector>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#define FS 15
#define PMAX 200
#define PMIN 5
#define H 60
#include "qcustomplot.h"
#include "Vector.h"
#include "derivedealgo.h"
#include <QDebug>
#include <QEvent>

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


private:
    QCustomPlot *plot;
    Vector<double> x,y;
    QPushButton *quit;
    QLabel *info;

};

#endif // PLOTINGWIDGET_H

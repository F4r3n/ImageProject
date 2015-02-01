#include "derivedealgo.h"

DerivedAlgo::DerivedAlgo()
{
}

QVector<double>  DerivedAlgo::execute(QVector<double> x,QVector<double> y) {
    QVector<double> dy(y.size()+1);
    for(int i=1;i<x.size();i++) {
        dy[i] = (y[i]-y[i-1]);
    }

    return dy;
}

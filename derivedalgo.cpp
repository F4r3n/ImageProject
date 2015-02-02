#include "derivedealgo.h"

DerivedAlgo::DerivedAlgo()
{
}

QVector<double>  DerivedAlgo::execute(const QVector<double> &x,const QVector<double> &y) {
    QVector<double> dy(y.size());
    for(int i=1;i<x.size();i++) {
        dy[i] = (y[i]-y[i-1]);
    }
    return dy;
}

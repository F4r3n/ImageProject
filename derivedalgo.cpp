#include "derivedealgo.h"

DerivedAlgo::DerivedAlgo()
{
}

Vector<double> DerivedAlgo::execute(const Vector<double> &x, const Vector<double> &y) {
    Vector<double> dy(y.size());
    for(int i=1;i<x.size();i++) {
        dy[i] = (y[i]-y[i-1]);
    }
    return dy;
}

#include "derivedealgo.h"

DerivedAlgo::DerivedAlgo()
{
}

Vector<double> DerivedAlgo::execute(const Vector<double> &x, const Vector<double> &y) {
    if(y.size()==0) return 0;
    Vector<double> dy(y.size());
    if(y.size()>=1)
    dy[0] = 0;
    for(int i=1;i<x.size();i++) {
        dy[i] = (y[i]-y[i-1]);
    }
    return dy;
}

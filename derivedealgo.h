#ifndef AVERAGEALGO_H
#define AVERAGEALGO_H

#include "strategie.h"

class DerivedAlgo : public Strategie
{
public:
    DerivedAlgo();
    Vector<double> execute(const Vector<double> &x,const Vector<double> &y);
};

#endif // AVERAGEALGO_H

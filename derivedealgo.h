#ifndef AVERAGEALGO_H
#define AVERAGEALGO_H

#include "strategie.h"

class DerivedAlgo : public Strategie
{
public:
    DerivedAlgo();
    QVector<double> execute(const QVector<double> &x,const QVector<double> &y);
};

#endif // AVERAGEALGO_H

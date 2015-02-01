#ifndef AVERAGEALGO_H
#define AVERAGEALGO_H

#include "strategie.h"

class DerivedAlgo : public Strategie
{
public:
    DerivedAlgo();
    QVector<double> execute(QVector<double> x, QVector<double> y);
};

#endif // AVERAGEALGO_H

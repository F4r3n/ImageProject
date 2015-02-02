#ifndef STRATEGIE_H
#define STRATEGIE_H

#include <QVector>

class Strategie
{
public:
    Strategie();
    virtual ~Strategie();
    virtual QVector<double> execute(const QVector<double> &x,const QVector<double> &y)=0;
};

#endif // STRATEGIE_H

#ifndef STRATEGIE_H
#define STRATEGIE_H

#include "Vector.h"

class Strategie
{
public:
    Strategie();
    virtual ~Strategie();
    virtual Vector<double> execute(const Vector<double> &x,const Vector<double> &y)=0;
};

#endif // STRATEGIE_H

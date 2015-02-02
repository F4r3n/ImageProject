#ifndef TFD_H
#define TFD_H

#include "strategie.h"
#include "Vector.h"
#include <cmath>
#include <QDebug>

class Tfd : public Strategie
{
public:
    Tfd();
    Vector<double> execute(const Vector<double> &x,const Vector<double> &y);

};

#endif // TFD_H

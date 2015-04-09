#ifndef TFD_H
#define TFD_H

#include "strategie.h"
#include "Vector.h"
#include <cmath>
#include "plotingwidget.h"
#include <QDebug>

class Tfd : public Strategie
{
public:
    Tfd();
    Vector<double> execute(const Vector<double> &x,const Vector<double> &y);
    Vector<double> getImg();
    Vector<double> getRe();
    Vector<double> filter(int N);
    void lowPassFilter(double *re,double *im, int N);
    Vector<double> inverse(const Vector<double> &ReOutput, const Vector<double> &ImOutput, int N);
    Vector<double> hamming(double n);


private:
    Vector<double> _re;
    Vector<double> _im;

};

#endif // TFD_H

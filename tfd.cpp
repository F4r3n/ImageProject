#include "tfd.h"

Tfd::Tfd()
{
}

Vector<double> Tfd::execute(const Vector<double> &x,const Vector<double> &y){

    unsigned int size = x.size();
    Vector<double> re(size);
    unsigned int n = 2*size;
    Vector<double> v(n);

    for (unsigned int k = 0; k < size; k++) {  /* For each output element */
        double sumreal = 0;
        double sumimag = 0;
        unsigned int t;
        for (t = 0; t < size; t++) {  /* For each input element */
            double angle = 2 * M_PI * t * k / n;
            sumreal +=  y[t] * cos(angle);
            sumimag += -y[t] * sin(angle);
        }
        v[k] = sumreal;
        //  outimag[k] = sumimag;
    }


    return v;
}

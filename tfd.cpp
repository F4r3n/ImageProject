#include "tfd.h"

Tfd::Tfd()
{
}

Vector<double> Tfd::execute(const Vector<double> &x,const Vector<double> &y){

    unsigned int size = x.size();
    qDebug() << "Taille "<<size;
    Vector<double> v(size);

    for (unsigned int k = 0; k < size; k++) {  /* For each output element */
        double sumreal = 0;
        double sumimag = 0;
        unsigned int t;
        for (t = 0; t < size; t++) {  /* For each input element */
            double angle = 2 * M_PI * (t * k) / (float)size;
            sumreal +=  y[t] * cos(angle);
            sumimag += -y[t] * sin(angle);
            qDebug() << t*k/size;
        }
        //qDebug() << sumreal;
        v[k] = sumreal;
        //  outimag[k] = sumimag;
    }


    return v;
}

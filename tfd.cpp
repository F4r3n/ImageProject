#include "tfd.h"

Tfd::Tfd()
{

}

Vector<double> Tfd::hamming(double n) {
    Vector<double> in;
    for(int i=0;i<n;i++) {
        in.push_back(0.54-0.46*cos((double)2*M_PI*i/(double)(n)));
    }
    return in;
}

Vector<double> Tfd::execute(const Vector<double> &x,const Vector<double> &in){

    qDebug() << x.size();
    Vector<double> y(x.size());
    std::copy(in.begin(),in.end(),y.begin());
  //  Vector<double> window = hamming(in.size());
   // for(int i=0;i<in.size();i++) {
     //   y[i] *= window[i];
    //}
    unsigned int size = x.size();
    Vector<double> re(size);
    Vector<double> im(size);

    for (unsigned int k = 0; k < size/2; k++) {  /* For each output element */
        double sumreal = 0;
        double sumimag = 0;
        unsigned int t;
        for (t = 0; t < size; t++) {  /* For each input element */
            double angle = 2 * M_PI * (t * k) / ((float)size);
            sumreal +=  y[t] * cos(angle);
            sumimag -= y[t] * sin(angle);
        }
        //qDebug() << sumreal;
        re[k] = fabs(sumreal)/(size/2);
        im[k] = fabs(sumimag)/(size/2);

    }

    _re.resize(y.size());
    _im.resize(y.size());

    std::copy(re.begin(),re.end(),_re.begin());
    std::copy(im.begin(),im.end(),_im.begin());


    return re;
}

void Tfd::highPassFilter(double *re,double *im, int N) {

}

void Tfd::bandPassFilter(double *re,double *im, int N) {

}

void Tfd::lowPassFilter(double *re,double *im, int N) {
    double alpha=50.0;

    for(int f=0;f<(N/2);f++) {
        double w = 2*M_PI*f;
        re[f]=alpha*alpha/(alpha*alpha+w*w);
        im[f]=0;
    }
}

Vector<double> Tfd::getRe() {
    return _re;
}

Vector<double> Tfd::filter(int N) {

    double ReFil[N/2+1];
    double ImFil[N/2+1];

    lowPassFilter(ReFil,ImFil,N);

    Vector<double> ReOutput(N);
    Vector<double> ImOutput(N);

    for(int f=0;f<N/2;f++) {
        ReOutput[f]=(double)(_re[f]*ReFil[f]-_im[f]*ImFil[f]);
        ImOutput[f]=(double)(_re[f]*ImFil[f]+_im[f]*ReFil[f]);
    }

    return inverse(ReOutput,ImOutput,N);

}

Vector<double> Tfd::getImg() {
    return _im;
}

Vector<double> Tfd::inverse(const Vector<double> &ReOutput, const Vector<double> &ImOutput,int N) {
    Vector<double> output(N);
    for(int f=0;f<(N/2);f++) {
        for(int i=0;i<N;i++) {
            double w = 2*M_PI*(double)i/N;
            output[i]+=ReOutput[f]*cos(f*w)-ImOutput[f]*sin(f*w);
        }
    }

    return output;
}


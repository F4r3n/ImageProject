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
    /*!
     * \brief Permet de faire une FFT
     * \param x
     * \param y
     * \return
     */
    Vector<double> execute(const Vector<double> &x,const Vector<double> &y);
    Vector<double> getImg();
    Vector<double> getRe();
    /*!
     * \brief lance la fonction permettant de faire un filtre passe-bas et récupère celles-ci.
     * \param N
     * \return
     */
    Vector<double> filter(int N);
    /*!
     * \brief Filtre passe bas
     * \param re
     * \param im
     * \param N
     */
    void lowPassFilter(double *re,double *im, int N);
    /*!
     * \brief Permet de faire une FFT inverse
     * \param ReOutput
     * \param ImOutput
     * \param N
     * \return
     */
    Vector<double> inverse(const Vector<double> &ReOutput, const Vector<double> &ImOutput, int N);
    /*!
     * \brief Permet de faire une fenêtre de Hamming
     * \param n
     * \return
     */
    Vector<double> hamming(double n);


private:
    Vector<double> _re;
    Vector<double> _im;

};

#endif // TFD_H

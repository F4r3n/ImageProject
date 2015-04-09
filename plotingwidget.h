#ifndef PLOTINGWIDGET_H
#define PLOTINGWIDGET_H

#include <QDialog>
#include <QVector>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QEvent>
#include "qcustomplot.h"
#include "Vector.h"
#include "derivedealgo.h"


class PlotingWidget : public QDialog
{

public:
    explicit PlotingWidget(Vector<double> x, Vector<double> y, int n,QString name ="Plot" , QWidget *parent = 0 );
    /*!
     * \brief Permet d'obtenir la valeur minimale d'une fonction
     * \param z
     * \return
     */
    double minValue(const Vector<double> &z);
    /*!
     * \brief Permet d'obtenir la valeur maximale d'une fonction
     * \param z
     * \return
     */
    double maxValue(const Vector<double> &z);
    /*!
     * \brief Fonction de trigger
     * \param z
     * \return
     */
    int variation(const Vector<double> &z);
    /*!
     * \brief Calcul de la fréquence en fonction du FPS
     * \param v
     * \return
     */
    double frequency(int v);
    int maxX();
    int minX();
    double maximaLocal(int deb, int end);
    double frequencyTFD();
    /*!
     * \brief Permet d'ajouter un graphe au graphique existant
     * \param x
     * \param y
     * \param name
     * \param pen
     * \param rescale
     */
    void addGraph(Vector<double> x, Vector<double> y, QString name, QPen pen, bool rescale);


private:
    short nbGraph = 0;
    QCustomPlot *plot;
    Vector<double> x,y;
    QPushButton *quit;
    QLabel *info;

};

#endif // PLOTINGWIDGET_H

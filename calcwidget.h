#ifndef CALCWIDGET_H
#define CALCWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QRect>
#include <QTextEdit>
#include "labelimage.h"
#include "plotingwidget.h"
#include <QVector>
#include "derivedealgo.h"
#include "spc.h"
#include <QCheckBox>
#include <QScrollArea>
#include "tfd.h"
#include <Vector.h>

class CalcWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CalcWidget(LabelImage *label);
    void setImages(std::vector<QImage> *img);
    /*!
     * \brief Permet de faire la dérivée d'un Vector
     * \param y
     * \return
     */
    Vector<double> derived(const Vector<double> &y) const;
    /*!
     * \brief afficheles données dans l'afficheur pour l'algorithme 1
     */
    void displayData();
    /*!
     * \brief choisi l'espace de couleur
     * \param type
     */
    void setType(int type);
    /*!
     * \brief Permet de faire une moyenne glissante d'une fonction
     * \param z
     */
    void movingAverage(Vector<double> &z) const;
    /*!
     * \brief Affiche les données pour l'algorithme 2
     */
    void displayDataColor();
    /*!
     * \brief Permet de faire une dérivée de Taylor, utilisé pour l'algorithme 2
     */
    void amplified();

signals:
    void clicked(QImage img);

public slots:
    /*!
     * \brief Calcul avec l' algorithme 1
     * \return
     */
    bool calculus(); /*!
     * \brief Calcul avec l' algorithme 2
     * \return
     */
    bool calculusColor();
    /*!
     * \brief Permet de voir la frame suivante
     */
    void nextImage();
    /*!
     * \brief Permet de voir la frame précédente
     */
    void previousImage();
    /*!
     * \brief Permet de lancer l'analyse avec un algorithme choisit
     */
    void analyzeImages();
    /*!
     * \brief Permet de remettre les images au début
     */
    void rewindImages();
    /*!
     * \brief Permet le choix de l'algoritme a utiliser
     * \param btnChecked
     */
    void optionCalc(int btnChecked);
    void redirectCalculus();

private:
    QPushButton *calc;
    QTextEdit *result;
    QRect *rect;
    LabelImage *lab;
    QPushButton *next;
    QPushButton *previous;
    std::vector<QImage> images;
    QScrollArea *area;
    QPushButton *analyze;
    QPushButton *rewind;
    Vector<double> x;
    Vector<double> y;
    Vector<double> yr;
    Vector<double> yg;
    Vector<double> yb;

    QCheckBox *averageBox;
    QCheckBox *derivedBox;
    QCheckBox *amplificationBox;
    QCheckBox *amplificationDerivedBox;
    QCheckBox *derivedSBox;

    Vector<Vector<double> > squares;
    const int squareSize = 10;

    unsigned int index;
    int type;
    bool analyseColor;

};

#endif // CALCWIDGET_H

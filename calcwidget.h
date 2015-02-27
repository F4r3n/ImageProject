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
    Vector<double> derived(const Vector<double> &y) const;
    void displayData();
    void setType(int type);
    void movingAverage(Vector<double> &z) const;
    void displayDataColor();
    void amplified();

signals:
    void clicked(QImage img);

public slots:
    bool calculus();
    bool calculusColor();
    void nextImage();
    void previousImage();
    void analyzeImages();
    void rewindImages();
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

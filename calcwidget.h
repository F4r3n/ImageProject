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


signals:
    void clicked(QImage img);
public slots:
    bool calculus();
    void nextImage();
    void previousImage();
    void analyzeImages();
    void rewindImages();

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
    QCheckBox *averageBox;
    QCheckBox *derivedBox;
    QCheckBox *amplificationBox;
    QCheckBox *amplificationDerivedBox;
    QCheckBox *derivedSBox;


    unsigned int index;
    int type;

};

#endif // CALCWIDGET_H

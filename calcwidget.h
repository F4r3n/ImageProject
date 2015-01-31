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
#include <QCheckBox>
#include <QScrollArea>

class CalcWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CalcWidget(LabelImage *label);
    void setImages(std::vector<QImage> *img);
    QVector<double> derived();
    void displayData();
    void movingAverage(QVector<double> &z);


signals:
    void clicked(QImage img);
public slots:
    void calculus();
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
    QVector<double> x;
    QVector<double> y;
    QCheckBox *averageBox;
    QCheckBox *derivedBox;
    unsigned int index;

};

#endif // CALCWIDGET_H

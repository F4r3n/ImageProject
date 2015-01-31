#ifndef CALCWIDGET_H
#define CALCWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QRect>
#include "labelimage.h"

class CalcWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CalcWidget(LabelImage *label);
    void setImages(std::vector<QImage> *img);

signals:
    void clicked(QImage img);
public slots:
    void calculus();
    void nextImage();
    void previousImage();

private:
    QPushButton *calc;
    QLabel *result;
    QRect *rect;
    LabelImage *lab;
    QPushButton *next;
    QPushButton *previous;
    std::vector<QImage> images;
    unsigned int index;

};

#endif // CALCWIDGET_H

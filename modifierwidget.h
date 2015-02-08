#ifndef MODIFIERWIDGET_H
#define MODIFIERWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QSlider>
#include <QGridLayout>
#include <QImage>
#include "labelimage.h"

class ModifierWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ModifierWidget(LabelImage *parent = 0);
    void setGray(QImage &img);
    void setBorderX(QImage &img);
    void setGaussianBlur(QImage &image);
    float **kernelBox(int r);
    float computePixelBox(QImage &img, float **box,int x,int y,int n);


signals:

public slots:
    void toGray(bool c);
    void toBlur(bool c);

private:
    LabelImage *labelImage;
    QCheckBox *grayBox;
    QCheckBox *edgeBox;
    QCheckBox *smoothBox;
    QSlider *smoothSlider;
    QImage img;
    QImage beforeImg;

};

#endif // MODIFIERWIDGET_H
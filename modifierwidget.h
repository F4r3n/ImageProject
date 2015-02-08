#ifndef MODIFIERWIDGET_H
#define MODIFIERWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QSlider>
#include <QGridLayout>
#include <QImage>
#include <QPushButton>
#include <vector>
#include "labelimage.h"

class ModifierWidget : public QWidget
{
    Q_OBJECT
private:
    int getSign(int a);

public:
    explicit ModifierWidget(LabelImage *parent = 0);
    void setGray(QImage &img);
    void setBorderX(QImage &img);
    void setGaussianBlur(QImage &image);
    float **kernelBox(int r);
    float computePixelBox(QImage &img, float **box,int x,int y,int n);
    void setCLTBlur(QImage &img,int n);
    void saveImage(const QImage &img);



signals:

public slots:
    void toGray(bool c);
    void toBlur(bool c);
    void toEdge(bool c);
    void resetImage();
    void toBlurCLT(bool c);

private:

    LabelImage *labelImage;
    QCheckBox *grayBox;
    QCheckBox *edgeBox;
    QCheckBox *smoothBox;
    QCheckBox *cltBox;
    QSlider *smoothSlider;
    QImage img;
    QImage beforeImg;
    QPushButton *resetButton;
    std::vector<QCheckBox*> tabBox;

};

#endif // MODIFIERWIDGET_H

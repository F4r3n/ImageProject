#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QString>
#include <QGridLayout>
#include <QRgb>
#include <QPoint>
#include <QTextStream>
#include <QPushButton>
#include <vector>
#include <QRgb>
#include "calcwidget.h"
#include "spc.h"
#include "labelimage.h"
#include "optionwidget.h"

class RenderArea : public QWidget
{

public:
    explicit RenderArea(QWidget *parent = 0);
    void setImages(std::vector<QImage> *img);
    QString getInfo();
    int getType();
    void setType(int type);
    void setGray(QImage &img);
    void setBorderX(QImage &img);

signals:

public slots:

private:
    QImage img;
    LabelImage *labelImage;
    QString *info;
    QRgb rgb;
    std::vector<QImage> images;
    CalcWidget *calc;

    OptionWidget *optionW;
    int type;

};

#endif // RENDERAREA_H

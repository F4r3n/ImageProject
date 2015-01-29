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

#include "labelimage.h"

class RenderArea : public QWidget
{

public:
    explicit RenderArea(QWidget *parent = 0);
    void setImage(QImage *img);
    QString getInfo();



signals:

public slots:

private:
    QImage img;
    LabelImage *labelImage;
    QString *info;
    QRgb rgb;

};

#endif // RENDERAREA_H

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
#include "calcwidget.h"
#include "spc.h"

#include "labelimage.h"

class RenderArea : public QWidget
{

public:
    explicit RenderArea(QWidget *parent = 0);
    void setImage(QImage *img);
    QString getInfo(int type);

signals:

public slots:

private:
    QImage img;
    LabelImage *labelImage;
    QString *info;
    QRgb rgb;
    CalcWidget *calc;

};

#endif // RENDERAREA_H

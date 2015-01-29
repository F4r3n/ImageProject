#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QString>
#include <QGridLayout>
#include "labelimage.h"

class RenderArea : public QWidget
{

public:
    explicit RenderArea(QWidget *parent = 0);
    void setImage(QImage *img);


signals:

public slots:

private:
    QImage img;
    LabelImage *labelImage;
    QString *info;

};

#endif // RENDERAREA_H

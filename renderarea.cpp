#include "renderarea.h"
#include <iostream>

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent)
{
    resize(600,400);

    QGridLayout *grid = new QGridLayout();
    setLayout(grid);
    img.load("visage3.jpg");
    info = new QString();
    if(img.isNull()){
        info->append("Image Nulle");
    }

    labelImage = new LabelImage(this);
    setStyleSheet("background-color:black;");
    labelImage->setImage(&img);
    grid->addWidget(labelImage);


}

void RenderArea::setImage(QImage *img) {
    labelImage->setImage(img);
}

QString RenderArea::getInfo(int type) {
    rgb = labelImage->getRgb();
    QPoint point = labelImage->getPos();
    QString info;
    QColor c(rgb);
    QTextStream s(&info);
    if(type ==1) {
        c.toHsl();
        s << point.x() << ", " << point.y() << " " << c.hslHue();

    } else {
        s << point.x() << ", " << point.y() << " " << c.red() << " " << c.green() <<" " << c.blue();

    }


    return info;
}



#include "renderarea.h"
#include <iostream>

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent)
{
    resize(600,600);
    QGridLayout *grid = new QGridLayout();
    setLayout(grid);
  //  img.load("visage3.jpg");
    info = new QString();
    if(img.isNull()){
        info->append("Image Nulle");
    }
    labelImage = new LabelImage(this);
    calc = new CalcWidget(labelImage);

    //setStyleSheet("background-color:black;");
    //labelImage->setImage(&img);

    grid->addWidget(labelImage);
    grid->addWidget(calc,0,1);

}

int RenderArea::getType() {
    return type;
}

void RenderArea::setType(int type) {
    this->type = type;
    calc->setType(type);
}

void RenderArea::setImages(std::vector<QImage> *img) {
    this->images = *img;
    labelImage->setImage(&images[0]);
    calc->setImages(&images);
}

QString RenderArea::getInfo() {
    rgb = labelImage->getRgb();
    QPoint point = labelImage->getPos();
    QString info;
    QColor c(rgb);
    QTextStream s(&info);
    if(type==RGB){
        s << point.x() << ", " << point.y() << " " << c.red() << " " << c.green() <<" " << c.blue();
    }

    if(type ==HSL) {
        c.toHsl();
        s << point.x() << ", " << point.y() << " " << c.hslHue() << " " << c.hslSaturation() << " " <<c.lightness();
    }
    if(type ==HSV) {
        c.toHsv();
        s << point.x() << ", " << point.y() << " " << c.hsvHue() << " " << c.hsvSaturation() << " " <<c.lightness();
    }

    return info;
}



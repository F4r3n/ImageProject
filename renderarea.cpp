#include "renderarea.h"
#include <iostream>

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent)
{
    type = 0;
    resize(600,600);
    QGridLayout *grid = new QGridLayout();
    setLayout(grid);
    info = new QString();
    if(img.isNull()){
        info->append("Image Nulle");
    }
    labelImage = new LabelImage(this);
    calc = new CalcWidget(labelImage);

    grid->addWidget(labelImage);
    grid->addWidget(calc,0,1);

}

void RenderArea::setGray(QImage &img) {
    QRgb col;
    int gray;
    for(int i=0;i<img.width();++i) {
        for(int j=0;j<img.height();++j) {
            col = img.pixel(i,j);
            gray =qGray(col);
            img.setPixel(i,j,qRgb(gray,gray,gray));
        }
    }
}

void RenderArea::setBorderX(QImage &img) {

    for(int i=0;i<img.width();++i) {
        bool up = false;
        bool down = false;
        for(int j=0;j<img.height()-1;++j) {
            QRgb a = img.pixel(i,j);
            QRgb b = img.pixel(i,j+1);
            int c = a-b;

            if((down == true && c>0) || (up == true && c<0) ) img.setPixel(i,j,qRgb(255,255,255));
            else img.setPixel(i,j,qRgb(0,0,0));


            if(c<0) {
                down = true;
                up=false;
            }
            if(c>0) {
                up =true;
                down = false;
            }
        }
    }
}

int RenderArea::getType() {
    return type;
}

void RenderArea::setType(int type) {
    this->type = type;
    calc->setType(type);
}

void RenderArea::setImages(std::vector<QImage> *img) {
    images = *img;
    //for(QImage &i : images) {
     //   setGray(i);
      //  setBorderX(i);
    //}
    labelImage->setImage(&images[0]);
    calc->setImages(&images);
}

QString RenderArea::getInfo() {
    rgb = labelImage->getRgb();
    QPoint point = labelImage->getPos();
    QString info;
    QColor c(rgb);
    QTextStream s(&info);

    QImage i = labelImage->getImg();
    if(point.x() > i.width() || point.y() > i.height()) {
        s << point.x() << ", " << point.y() << " ";
        return info;
    }
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
    if(type == LI) {
        s << point.x() << ", " << point.y() << " " << c.lightness() << " ";
    }

    if(type == HUE) {
        s << point.x() << ", " << point.y() << " " << c.hslHue() << " ";
    }


    return info;
}



#include "renderarea.h"
#include <iostream>

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *grid = new QGridLayout();
    setLayout(grid);
    img.load("visage.jpg");
    info = new QString();
    if(img.isNull()){
        info->append("Image Nulle");
        std::cout << "Pas d'image";
    }

    labelImage = new QLabel();
    setStyleSheet("background-color:black;");
    labelImage->setPixmap(QPixmap::fromImage(img));
    grid->addWidget(labelImage);
    resize(800,500);


}

void RenderArea::setImage(QImage *img) {
    this->img = *img;
    labelImage->setPixmap(QPixmap::fromImage(this->img));
    if(this->img.width() > this->width() ) {
        resizeImage(this->width(),this->height());
    }
}

void RenderArea::resizeImage(int w, int h) {
    QPixmap pixmap;
    pixmap = pixmap.fromImage(img.scaled(w,h,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    labelImage->setPixmap(pixmap);
}

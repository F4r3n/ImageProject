#include "labelimage.h"
#include <iostream>

LabelImage::LabelImage(QWidget *parent) :
    QLabel(parent)
{
    setMouseTracking(true);
    w = parent->width();
    h = parent->height();
}

void LabelImage::mouseMoveEvent(QMouseEvent *event){
    x = event->pos().x();
    y = event->pos().y();
    //QRgb rgb = this->pixmap()->toImage().pixel(x,y);
}

QPoint LabelImage::getPos() {
    return QPoint(x,y);
}

QRgb LabelImage::getRgb() {
    return img.pixel(x,y);
}

void LabelImage::setImage(QImage *img) {
    this->img = *img;
    if(this->img.width() > w ) {
        resizeImage(w,h);
    } else {
        setPixmap(QPixmap::fromImage(this->img));
    }

}

void LabelImage::resizeImage(int w, int h) {
    img = img.scaled(w,h,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    setPixmap(QPixmap::fromImage(img));
}

void LabelImage::drawImage() {
    setPixmap(QPixmap::fromImage(img));
}

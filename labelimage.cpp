#include "labelimage.h"
#include <iostream>

LabelImage::LabelImage(QWidget *parent) :
    QLabel(parent)
{
    setMouseTracking(true);
    w = parent->width();
    h = parent->height();
    onDrawingRect = false;
    setMouseTracking(true);
}

void LabelImage::mouseMoveEvent(QMouseEvent *event){
    x = event->pos().x();
    y = event->pos().y();
    if(onDrawingRect) repaint();
    //QRgb rgb = this->pixmap()->toImage().pixel(x,y);
}

void LabelImage::mousePressEvent(QMouseEvent *event) {
    if(!onDrawingRect) {
        onDrawingRect = true;
        pos1 = event->pos();
        std::cout << "pos1 " << pos1.x()<<std::endl;
    }else {
        std::cout << "pos2 " << pos2.x()<<std::endl;

        pos2 = event->pos();
    }
    repaint();

}

void LabelImage::mouseReleaseEvent(QMouseEvent *event) {
    if(onDrawingRect) {
        onDrawingRect = false;
        pos1 = QPoint(0,0);
        pos2 = QPoint(0,0);

    }
}


void LabelImage::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setPen(QPen(Qt::blue,1));
    painter.drawImage(1,1,img);

    if(onDrawingRect) {
        qDebug() << "inside";
        painter.drawRect(QRect(pos1,QPoint(x,y)));
    }
}

QPoint LabelImage::getPos() {
    return QPoint(x,y);
}

QRgb LabelImage::getRgb() {
    if(x!=-1)
        return img.pixel(x,y);
    else return 0;
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

#include "labelimage.h"
#include <iostream>

LabelImage::LabelImage(QWidget *parent) :
    QLabel(parent)
{
    setMouseTracking(true);
    w = parent->width();
    h = parent->height();
    x=-1;
    y=-1;
    onDrawingRect = false;
    inside  = false;
    setMouseTracking(true);
}

void LabelImage::enterEvent(QEvent *) {
    inside = true;
}

void LabelImage::leaveEvent(QEvent *) {
    inside = false;
}

void LabelImage::mouseMoveEvent(QMouseEvent *event){
    x = event->pos().x();
    y = event->pos().y();
    if(time.elapsed() > 50) {
        time.restart();
        if(onDrawingRect) repaint();
    }
}

void LabelImage::mousePressEvent(QMouseEvent *event) {
    if(!onDrawingRect) {
        time.start();
        onDrawingRect = true;
        pos1 = event->pos();
    }else {
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
        if(inside)
            painter.drawRect(QRect(pos1,QPoint(x,y)));
    }
}

QPoint LabelImage::getPos() {
    return QPoint(x,y);
}

QRgb LabelImage::getRgb() {
    if(inside)
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

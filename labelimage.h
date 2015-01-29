#ifndef LABELIMAGE_H
#define LABELIMAGE_H

#include <QLabel>
#include <QMouseEvent>
#include <QImage>
#include <QPoint>
#include <QRgb>
#include <QPainter>
#include <QDebug>

class LabelImage : public QLabel
{
    Q_OBJECT
public:
    explicit LabelImage(QWidget *parent = 0);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void drawImage();
    void paintEvent(QPaintEvent *p);
    void setImage(QImage *img);
    void resizeImage(int w, int h);
    QPoint getPos();
    QRgb getRgb();



signals:

public slots:

private:
    int x;
    int y;
    QImage img;
    int w,h;
    QPoint pos1,pos2;
    bool onDrawingRect;

};

#endif // LABELIMAGE_H

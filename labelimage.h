#ifndef LABELIMAGE_H
#define LABELIMAGE_H

#include <QLabel>
#include <QMouseEvent>
#include <QImage>

class LabelImage : public QLabel
{
    Q_OBJECT
public:
    explicit LabelImage(QWidget *parent = 0);
    void mouseMoveEvent(QMouseEvent *event);
    void drawImage();
    void setImage(QImage *img);
    void resizeImage(int w, int h);


signals:

public slots:

private:
    int x;
    int y;
    QImage img;
    int w,h;

};

#endif // LABELIMAGE_H

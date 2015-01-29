#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QString>
#include <QGridLayout>

class RenderArea : public QWidget
{

public:
    explicit RenderArea(QWidget *parent = 0);
    void setImage(QImage *img);
    void resizeImage(int w, int h);




signals:

public slots:

private:
    QImage img;
    QLabel *labelImage;
    QString *info;

};

#endif // RENDERAREA_H

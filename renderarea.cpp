#include "renderarea.h"
#include <iostream>

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent)
{
    resize(600,400);

    QGridLayout *grid = new QGridLayout();
    setLayout(grid);
    img.load("visage.jpg");
    info = new QString();
    if(img.isNull()){
        info->append("Image Nulle");
        std::cout << "Pas d'image";
    }

    labelImage = new LabelImage(this);
    setStyleSheet("background-color:black;");
    labelImage->setImage(&img);
    grid->addWidget(labelImage);


}

void RenderArea::setImage(QImage *img) {
   labelImage->setImage(img);
}



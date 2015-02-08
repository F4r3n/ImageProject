#include "modifierwidget.h"

ModifierWidget::ModifierWidget(LabelImage *parent)
{
    labelImage = parent;
    QGridLayout *gr = new QGridLayout();
    setLayout(gr);
    grayBox = new QCheckBox("Gray");
    edgeBox = new QCheckBox("Edge");
    smoothBox = new QCheckBox("smooth");

    smoothSlider = new QSlider();
    gr->addWidget(grayBox,0,0);
    gr->addWidget(edgeBox,0,1);
    gr->addWidget(smoothSlider,1,0);
    gr->addWidget(smoothBox,1,1);

    connect(smoothBox,SIGNAL(toggled(bool)),smoothSlider,SLOT(setDisabled(bool)));
    connect(grayBox,SIGNAL(toggled(bool)),this,SLOT(toGray(bool)));

}

void ModifierWidget::toGray(bool c) {

    if(c) {
    img = labelImage->getImg();

    beforeImg = img;

    setGray(img);
    } else {
        img = beforeImg;
    }
    labelImage->setImage(&img);
}

void ModifierWidget::setGray(QImage &img) {
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

void ModifierWidget::setBorderX(QImage &img) {

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

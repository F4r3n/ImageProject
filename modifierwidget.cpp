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
    smoothSlider->setMaximum(10);
    smoothSlider->setMinimum(0);
    gr->addWidget(grayBox,0,0);
    gr->addWidget(edgeBox,0,1);
    gr->addWidget(smoothSlider,1,0);
    gr->addWidget(smoothBox,1,1);

    connect(smoothBox,SIGNAL(toggled(bool)),smoothSlider,SLOT(setDisabled(bool)));
    connect(smoothBox,SIGNAL(toggled(bool)),this,SLOT(toBlur(bool)));
    connect(grayBox,SIGNAL(toggled(bool)),this,SLOT(toGray(bool)));
    connect(edgeBox,SIGNAL(toggled(bool)),this,SLOT(toEdge(bool)));


}

float **ModifierWidget::kernelBox(int r) {
    float **kernel =  new float*[r];
    for(int i = 0; i < r; ++i) {
        kernel[i] = new float[r];
    }
    double sigma = 1;
    double mean = r/2;
    double sum = 0.0;
    for (int x = 0; x < r; ++x)
        for (int y = 0; y < r; ++y) {
            kernel[x][y] = exp( -0.5 * (pow((x-mean)/sigma, 2.0) + pow((y-mean)/sigma,2.0)) )
                             / (2 * M_PI * sigma * sigma);

            sum += kernel[x][y];
        }

    for (int x = 0; x < r; ++x)
        for (int y = 0; y < r; ++y)
            kernel[x][y] /= sum;
    return kernel;
}

void ModifierWidget::toEdge(bool c) {
    if(c) {
    img = labelImage->getImg();
    beforeImg = img;
    setBorderX(img);
    } else {
        img = beforeImg;
    }
    labelImage->setImage(&img);
}

void ModifierWidget::toBlur(bool c) {
    if(c) {
    img = labelImage->getImg();
    beforeImg = img;
    setGaussianBlur(img);
    } else {
        img = beforeImg;
    }
    labelImage->setImage(&img);
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

float ModifierWidget::computePixelBox(QImage &img,float **box,int x,int y,int n) {
    float sum =0;
    for(int i=0;i<n;++i) {
        for(int j=0; j<n;j++) {
            QColor col(img.pixel(i+x,j+y));
            float r = col.red();

            sum +=r*box[i][j];
        }
    }
    return sum;
}


void ModifierWidget::setGaussianBlur(QImage &image) {
    int n = 9;
    float **box  = kernelBox(n);
    for(int i=n;i<image.width()-n;++i) {
        for(int j=n;j<image.height()-n;++j) {
            QColor c(image.pixel(j,i));
            float r = c.red();


            r = computePixelBox(image,box,i,j,n);
            image.setPixel(i,j,qRgb(r,r,r));
        }
    }
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

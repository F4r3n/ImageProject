#include "modifierwidget.h"

ModifierWidget::ModifierWidget(LabelImage *parent)
{
    labelImage = parent;
    QGridLayout *gr = new QGridLayout();
    setLayout(gr);
    grayBox = new QCheckBox("Gray");
    edgeBox = new QCheckBox("Edge");
    smoothBox = new QCheckBox("smooth");
    resetButton = new QPushButton("Reset");
    cltBox = new QCheckBox("CLT blur");
    tabBox.push_back(grayBox);
    tabBox.push_back(edgeBox);
    tabBox.push_back(smoothBox);
    tabBox.push_back(cltBox);




    smoothSlider = new QSlider();
    smoothSlider->setMaximum(10);
    smoothSlider->setMinimum(0);
    gr->addWidget(grayBox,0,0);
    gr->addWidget(edgeBox,0,1);
    gr->addWidget(smoothSlider,1,0);
    gr->addWidget(smoothBox,1,1);
    gr->addWidget(cltBox,1,2);

    gr->addWidget(resetButton,2,2);

    connect(smoothBox,SIGNAL(toggled(bool)),smoothSlider,SLOT(setDisabled(bool)));
    connect(smoothBox,SIGNAL(toggled(bool)),this,SLOT(toBlur(bool)));
    connect(cltBox,SIGNAL(toggled(bool)),this,SLOT(toBlurCLT(bool)));

    connect(grayBox,SIGNAL(toggled(bool)),this,SLOT(toGray(bool)));
    connect(edgeBox,SIGNAL(toggled(bool)),this,SLOT(toEdge(bool)));
    connect(resetButton,SIGNAL(clicked()),this,SLOT(resetImage()));

}

void ModifierWidget::saveImage(const QImage &img) {
    beforeImg = img;

}

void ModifierWidget::resetImage() {
    labelImage->setImage(&beforeImg);
    for(QCheckBox *c : tabBox)
        c->setChecked(false);
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
        setBorderX(img);
        labelImage->setImage(&img);
    }
}

void ModifierWidget::toBlur(bool c) {
    if(c) {
        img = labelImage->getImg();
        setGaussianBlur(img);
        labelImage->setImage(&img);
    }
}

void ModifierWidget::toBlurCLT(bool c) {
    if(c) {
        img = labelImage->getImg();
        setCLTBlur(img,5);
        labelImage->setImage(&img);
    }
}

void ModifierWidget::toGray(bool c) {

    if(c) {
        img = labelImage->getImg();
        setGray(img);
        labelImage->setImage(&img);
    }
}

float ModifierWidget::computePixelBox(QImage &img,float **box,int x,int y,int n) {
    float sum =0;
    for(int i=0;i<n;++i) {
        for(int j=0; j<n;j++) {
            QColor col(img.pixel(i+x-2,j+y-2));
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

int ModifierWidget::getSign(int a) {
    return (a>0)?1:0;
}

void ModifierWidget::setCLTBlur(QImage &img,int n) {
    for(int i=0;i<img.width();++i) {
        for(int j=0;j<img.height();++j) {

            int sum = 0;
            int nb = 0;
            for(int k=-n;k<n;k++) {
                if((j+k>0 && j+k<img.height())&& k!=0) {
                    QColor c(img.pixel(i,j+k));
                    sum+=c.red();
                    nb++;
                }
            }
            for(int k=-n;k<n;k++) {
                if((i+k>0 && i+k<img.width()) && k!=0) {
                    QColor c(img.pixel(i+k,j));
                    sum+=c.red();
                    nb++;
                }
            }
            sum+=QColor(img.pixel(i,j)).red();
            nb++;
            sum/=nb;
            img.setPixel(i,j,qRgb(sum,sum,sum));

        }
    }
}

void ModifierWidget::setBorderX(QImage &img) {

    for(int i=0;i<img.width();++i) {
        bool up = false;
        bool down = false;
        for(int j=0;j<img.height()-1;++j) {
            QColor a(img.pixel(i,j));
            QColor b(img.pixel(i,j+1));

            int c = a.red()-b.red();

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

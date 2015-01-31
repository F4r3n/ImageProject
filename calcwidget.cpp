#include "calcwidget.h"

CalcWidget::CalcWidget(LabelImage *label)
{
    index = 0;
    lab = label;
    QGridLayout *gr = new QGridLayout();
    setLayout(gr);
    calc = new QPushButton("Calcul");
    next = new QPushButton("Next");
    previous = new QPushButton("Previous");
    result = new QLabel("result");
    gr->addWidget(calc,0,0);
    gr->addWidget(next,0,1);
    gr->addWidget(previous,0,2);
    gr->addWidget(result);
    connect(calc,SIGNAL(clicked()),this,SLOT(calculus()));
    connect(next,SIGNAL(clicked()),this,SLOT(nextImage()));
    connect(previous,SIGNAL(clicked()),this,SLOT(previousImage()));
    connect(this,SIGNAL(clicked(QImage)),label,SLOT(nextImage(QImage)));

}

void CalcWidget::previousImage() {
    if(index > 0) {
        index--;
    }
    emit clicked(images[index]);
}

void CalcWidget::nextImage() {
    if(index < images.size()-1){
        index++;
    }
    emit clicked(images[index]);

}


void CalcWidget::calculus() {
    QRect *r = lab->getRect();
    if(!r) {
        result->setText(QString("No rect"));
        return;
    }
    float average = 0;
    QImage img = lab->getImg();
    int taille =0;
    //qDebug() << r->topLeft().y() << " " << r->bottomLeft().y();

    for(int i=r->topLeft().y();i<r->bottomLeft().y();++i){
        for(int j=r->topLeft().x();j<r->topRight().x();j++) {
            QColor c(img.pixel(j,i));
            average += (c.red()+c.green()+c.blue())/3.f;

            taille++;
        }
    }

    average = average/taille;
    result->setText(QString().setNum(average,'f'));

}

void CalcWidget::setImages(std::vector<QImage> *img) {
    images = *img;
}

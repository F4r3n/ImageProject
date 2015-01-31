#include "calcwidget.h"

CalcWidget::CalcWidget(LabelImage *label)
{
    index = 0;
    lab = label;
    QGridLayout *gr = new QGridLayout();
    area = new QScrollArea();
    setLayout(gr);
    calc = new QPushButton("Calcul");
    next = new QPushButton("Next");
    previous = new QPushButton("Previous");
    analyze = new QPushButton("Analyze");
    result = new QTextEdit();
    result->setReadOnly(true);
    result->setMinimumWidth(300);
    result->setMinimumHeight(600);

    gr->addWidget(calc,0,0);
    gr->addWidget(next,0,2);
    gr->addWidget(previous,0,1);
    area->setWidget(result);
    gr->addWidget(area);
    gr->addWidget(analyze,4,0);

    connect(calc,SIGNAL(clicked()),this,SLOT(calculus()));
    connect(next,SIGNAL(clicked()),this,SLOT(nextImage()));
    connect(previous,SIGNAL(clicked()),this,SLOT(previousImage()));
    connect(this,SIGNAL(clicked(QImage)),label,SLOT(nextImage(QImage)));
    connect(analyze,SIGNAL(clicked()),this,SLOT(analyzeImages()));


}

void CalcWidget::analyzeImages() {
    unsigned int i=0;
    while(i < images.size()) {
        calculus();
        nextImage();
        i++;
    }
    index = i;
}

void CalcWidget::previousImage() {
    if(images.size()==0) return;
    if(index > 0) {
        index--;
    }
    emit clicked(images[index]);
}

void CalcWidget::nextImage() {
    if(!images.size()) return;

    if(index < images.size()-1){
        index++;
    }
    emit clicked(images[index]);

}


void CalcWidget::calculus() {
  //  if(lab->getImg()==0) return;
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
    QString temp = result->toPlainText() + QString().setNum(average,'f');
    temp.append(QString("\n"));
    result->setText(temp);

}

void CalcWidget::setImages(std::vector<QImage> *img) {
    images = *img;
}

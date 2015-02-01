#include "calcwidget.h"

CalcWidget::CalcWidget(LabelImage *label)
{
    index = 0;
    lab = label;
    QGridLayout *gr = new QGridLayout();
    QGridLayout *s = new QGridLayout();
    type = RGB;

    area = new QScrollArea();
    setLayout(gr);
    calc = new QPushButton("Calcul");
    next = new QPushButton("Next");
    previous = new QPushButton("Previous");
    analyze = new QPushButton("Analyze");
    rewind = new QPushButton("Rewind");
    result = new QTextEdit();
    averageBox = new QCheckBox("Average");
    averageBox->setChecked(true);
    derivedBox = new QCheckBox("Derived");
    result->setReadOnly(true);
    derivedBox->setChecked(true);

    s->addWidget(result);
    gr->addWidget(calc,0,0);
    gr->addWidget(next,0,2);
    gr->addWidget(rewind,0,3);
    gr->addWidget(previous,0,1);
    area->setLayout(s);
    gr->addWidget(area,2,0,5,5);
    gr->addWidget(analyze,7,0);
    gr->addWidget(averageBox,7,1);
    gr->addWidget(derivedBox,7,2);


    connect(calc,SIGNAL(clicked()),this,SLOT(calculus()));
    connect(next,SIGNAL(clicked()),this,SLOT(nextImage()));
    connect(previous,SIGNAL(clicked()),this,SLOT(previousImage()));
    connect(this,SIGNAL(clicked(QImage)),label,SLOT(nextImage(QImage)));
    connect(analyze,SIGNAL(clicked()),this,SLOT(analyzeImages()));
    connect(rewind,SIGNAL(clicked()),this,SLOT(rewindImages()));


}

void CalcWidget::movingAverage(QVector<double> &z) {

    for(int i=1;i<x.size()-1;i++) {
        z[i] = (z[i]+z[i-1]+z[i+1])/3;
    }
}

QVector<double> CalcWidget::derived() {
   Strategie *s = new DerivedAlgo();
   QVector<double> dy = s->execute(x,y);
   movingAverage(dy);
   return dy;
}

void CalcWidget::rewindImages() {
    index = 0;
    emit clicked(images[index]);
}

void CalcWidget::analyzeImages() {
    if(images.size() == 0) return;
    result->clear();
    x.clear();
    y.clear();
    rewindImages();
    unsigned int i=index;
    while(i < images.size()) {
        calculus();
        displayData();
        nextImage();
        i++;

    }
    index = i;
    movingAverage(y);
    result->verticalScrollBar()->setSliderPosition(
                result->verticalScrollBar()->maximum());

    if(averageBox->isChecked()) {
        PlotingWidget *p = new PlotingWidget(x,y,QString("Average"),this);
        p->show();
    }
    if(derivedBox->isChecked()) {
        PlotingWidget *p = new PlotingWidget(x,derived(),QString("Derived"),this);
        p->show();
    }
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

void CalcWidget::displayData() {
    QString temp = result->toPlainText() + QString().setNum(y[y.size()-1],'f');
    temp.append(QString("\n"));
    result->setText(temp);
}

void CalcWidget::setType(int type) {
    this->type = type;
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

    for(int i=r->topLeft().y();i<r->bottomLeft().y();++i){
        for(int j=r->topLeft().x();j<r->topRight().x();j++) {
            QColor c(img.pixel(j,i));

            if(type==RGB) {
                average += (c.red()+c.green()+c.blue())/3.f;
            }
            if(type==HSV) {
                average += (c.hsvHue()+c.hsvSaturation()+c.lightness())/3.f;
            }
            if(type == HSL) {
                average += (c.hslHue()+c.hslSaturation()+c.lightness())/3.f;
            }
            if(type == LI){
                average+=c.lightness();
            }
            if(type == HUE){
                average+=c.hslHue();
            }

            taille++;
        }
    }

    average = average/taille;
    x.push_back(index);
    y.push_back(average);


}

void CalcWidget::setImages(std::vector<QImage> *img) {
    images = *img;
}

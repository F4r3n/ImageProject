#include "calcwidget.h"

CalcWidget::CalcWidget(LabelImage *label)
{
    index = 0;
    lab = label;
    QGridLayout *gr = new QGridLayout();
    QGridLayout *s = new QGridLayout();

    area = new QScrollArea();
    setLayout(gr);
    calc = new QPushButton("Calcul");
    next = new QPushButton("Next");
    previous = new QPushButton("Previous");
    analyze = new QPushButton("Analyze");
    rewind = new QPushButton("Rewind");
    result = new QTextEdit();
    averageBox = new QCheckBox("Average");
    derivedBox = new QCheckBox("Derived");
    result->setReadOnly(true);

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

QVector<double> CalcWidget::derived() {
    QVector<double> dy(y.size()+1);
    for(int i=1;i<x.size();i++) {
        dy[i] = (y[i]-y[i-1]);
    }
    qDebug() << x.size();
    return dy;
}

void CalcWidget::rewindImages() {
    index = 0;
    emit clicked(images[index]);
}

void CalcWidget::analyzeImages() {
    if(images.size() == 0) return;
    x.clear();
    y.clear();
    unsigned int i=index;
    while(i < images.size()) {
        calculus();
        displayData();
        nextImage();
        i++;
    }
    index = i;
    if(averageBox->isChecked()) {
        PlotingWidget *p = new PlotingWidget(x,y,this);
        p->show();
    }
    if(derivedBox->isChecked()) {
        PlotingWidget *p = new PlotingWidget(x,derived(),this);
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
            average += (c.red()+c.green()+c.blue())/3.f;

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

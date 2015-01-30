#include "calcwidget.h"

CalcWidget::CalcWidget(LabelImage *label)
{
    lab = label;
    QGridLayout *gr = new QGridLayout();
    setLayout(gr);
    calc = new QPushButton("Calcul");
    result = new QLabel("result");
    gr->addWidget(calc);
    gr->addWidget(result);
    connect(calc,SIGNAL(clicked()),this,SLOT(calculus()));
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

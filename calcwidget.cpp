#include "calcwidget.h"
#include <cmath>

CalcWidget::CalcWidget(LabelImage *label) {
    index = 0;
    lab = label;
    QGridLayout *gr = new QGridLayout();
    QGridLayout *s = new QGridLayout();
    type = RGB;
    analyseColor = false;

    area = new QScrollArea();
    setLayout(gr);
    calc = new QPushButton("Calcul");
    next = new QPushButton("Next");
    previous = new QPushButton("Previous");
    analyze = new QPushButton("Analyze");
    rewind = new QPushButton("Rewind");
    result = new QTextEdit();
    averageBox = new QCheckBox("Average");
    averageBox->setChecked(false);
    derivedBox = new QCheckBox("Derived");
    result->setReadOnly(true);
    derivedBox->setChecked(true);
    amplificationBox  = new QCheckBox("Amplification");
    amplificationDerivedBox  = new QCheckBox("Amplification derived");
    derivedSBox = new QCheckBox("FFT");
    derivedSBox->setChecked(true);

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
    gr->addWidget(amplificationBox,7,3);
    gr->addWidget(amplificationDerivedBox,7,4);
    gr->addWidget(derivedSBox,7,5);

    connect(calc,SIGNAL(clicked()),this,SLOT(redirectCalculus()));
    connect(next,SIGNAL(clicked()),this,SLOT(nextImage()));
    connect(previous,SIGNAL(clicked()),this,SLOT(previousImage()));
    connect(this,SIGNAL(clicked(QImage)),label,SLOT(nextImage(QImage)));
    connect(analyze,SIGNAL(clicked()),this,SLOT(analyzeImages()));
    connect(rewind,SIGNAL(clicked()),this,SLOT(rewindImages()));
}

void CalcWidget::redirectCalculus() {
    if(analyseColor) {
        calculusColor();
    } else {
        calculus();
    }
}


void CalcWidget::movingAverage(Vector<double> &z) const{
    if(z.size()==0) return ;
    for(int i=1;i<x.size()-1;i++) {
        z[i] = (z[i]+z[i-1]+z[i+1])/3;
    }
}

Vector<double> CalcWidget::derived(const Vector<double> &y) const {
    Strategie *s = new DerivedAlgo();
    Vector<double> dy = s->execute(x,y);
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
    yr.clear();
    yb.clear();
    yg.clear();
    rewindImages();
    unsigned int i=index;
    while(i < images.size()) {
        bool isOk;

        if(analyseColor) {
            isOk = calculusColor();
        } else {
            isOk = calculus();
        }

        if(!isOk)
            return;

        if(analyseColor) {
            displayDataColor();
        } else {
            displayData();
        }
        nextImage();
        i++;

    }
    index = i;

    if(analyseColor) {
        amplified();
    }
        movingAverage(y);
        if(analyseColor) {
            yg = y;
        }
qDebug() << "taille y" << y.size();

    //  result->verticalScrollBar()->setSliderPosition(
    //  result->verticalScrollBar()->maximum());
    Vector<double> cy(y);
    Vector<double> cyr(yr);
    Vector<double> cyb(yb);
    Vector<double> cyg(yg);
    int size = cyg.size();

    if(averageBox->isChecked()) {
        PlotingWidget *p = new PlotingWidget(x,cyg,size,QString("Average"),this);
  //      p->addGraph(x, cyr, QString("Red average"),QPen(Qt::red),true);
    //    p->addGraph(x, cyb, QString("Blue average"),QPen(Qt::blue),true);
      //  p->addGraph(x, cyg, QString("Green average"),QPen(Qt::darkGreen),true);
		p->show();
    }
    if(derivedBox->isChecked()) {
        PlotingWidget *p = new PlotingWidget(x,derived(cyg),size,QString("Derived"),this);
        //p->addGraph(x, derived(cyr), QString("Red average"),QPen(Qt::red),true);
       // p->addGraph(x, derived(cyb), QString("Blue average"),QPen(Qt::blue),true);
        //p->addGraph(x, derived(cyg), QString("Green average"),QPen(Qt::darkGreen),true);
        p->show();
    }
    if(amplificationBox->isChecked()) {
        double factor = 3;
        Vector<double> taylor = cy+multiply(derived(cy),factor);
        Vector<double> taylorRed = cy+multiply(derived(cyr),factor);
        Vector<double> taylorBlue = cy+multiply(derived(cyb),factor);
        Vector<double> taylorGreen = cy+multiply(derived(cyg),factor);

        PlotingWidget *p = new PlotingWidget(x,taylor,size,QString("Amplification"),this);
		p->addGraph(x, taylorRed, QString("Red average ampli"),QPen(Qt::red),true);
		p->addGraph(x, taylorBlue, QString("Blue average ampli"),QPen(Qt::blue),true);
		p->addGraph(x, taylorGreen, QString("Green average ampli"),QPen(Qt::darkGreen),true);
        p->show();
    }
    if(amplificationDerivedBox->isChecked()) {
        Vector<double> taylor = cy+derived(cy);
        PlotingWidget *p = new PlotingWidget(x,derived(taylor),size,QString("Amplification derived"),this);
        p->show();
    }

    if(derivedSBox->isChecked()) {
        Tfd *s = new Tfd();
        //On fait la fft avec le vert
        double n = x.size();
        double c=n;
        Vector<double> h = s->hamming(n);
        Vector<double> de = derived(cyg);
        qDebug() <<"t"<<de.size();
        for(int i=0;i<n;i++) {
            de[i] *=h[i];
        }

        for(int i=0;i<(1024-c);i++) {
            x.push_back(n);
            de.push_back(0);
            n++;
        }
        movingAverage(de);
   //     qDebug() << x;
//        qDebug() << cyr.size();

        Vector<double> d = s->execute(x,de);
       // d = s->filter(d.size());
       // d = s->execute(x,d);
     //   for(int i=0;i<c;i++) x[i] = i/0.1;
        PlotingWidget *pl = new PlotingWidget(x,d,1024,QString("FFT"),this);
        pl->show();
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

void CalcWidget::displayDataColor() {
    QString temp = result->toPlainText() + QString().setNum(squares[squares.size()-1][0],'f');
    temp.append(QString("\n"));
    result->setText(temp);
}

void CalcWidget::setType(int type) {
    this->type = type;
}


bool CalcWidget::calculus() {
    QRect *r = lab->getRect();
    if(!r) {
        result->setText(QString("No rect"));
        return false;
    }
    float average = 0, red_average = 0, blue_average = 0, green_average = 0;
    QImage img = lab->getImg();
    int taille =0;

    for(int i=r->topLeft().y();i<r->bottomLeft().y();++i){
        for(int j=r->topLeft().x();j<r->topRight().x();j++) {
            QColor c(img.pixel(j,i));

            if(type==RGB) {
				red_average += c.red();
				blue_average += c.blue();
				green_average += c.green(); 
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

	red_average = red_average/taille;
	blue_average = blue_average/taille;
	green_average = green_average/taille;
    average = average/taille;

    x.push_back(index);
    y.push_back(average);
    yr.push_back(red_average);
    yg.push_back(green_average);
    yb.push_back(blue_average);
    delete rect;
    return true;
}

void CalcWidget::setImages(std::vector<QImage> *img) {
    images = *img;
}


void CalcWidget::optionCalc(int btnChecked) {
    switch(btnChecked) {
        case -2:
            analyseColor = false;
            break;
        case -3:
            analyseColor = true;
            break;
        default:
            break;
    }
}

bool CalcWidget::calculusColor() {
    QRect *r = lab->getRect();
    if(!r) {
        result->setText(QString("No rect"));
        return false;
    }

    QImage img = lab->getImg();
    double average = 0;
    bool isOk = false;

    Vector<double> squaresAverages;

    for(int i=r->topLeft().y(); i<r->bottomLeft().y(); i+=squareSize){
        for(int j=r->topLeft().x(); j<r->topRight().x(); j+=squareSize) {
            average = 0;

            if(squareSize+i <= r->bottomLeft().y()) {
                for(int k=i; k<squareSize+i; k++) {
                    if(squareSize+j <= r->topRight().x()) {
                        for(int l=j; l<squareSize+j; l++) {
                            QColor c(img.pixel(l,k));
                            if(type == RGB) {
                                average += (c.red()+c.green()+c.blue())/3.f;
                            }
                            isOk = true;
                        }
                    }
                }
            }

            if(isOk) {
                average = average/(squareSize*squareSize);
                squaresAverages.push_back(average);
            }
            isOk = false;
        }
    }
    delete rect;
    squares.push_back(squaresAverages);
    x.push_back(index);
    return true;
}

void CalcWidget::amplified() {
    double factor = 5;
    double average = 0;

    for(int i=0;i<squares.size();i++) {
        Vector<double> temp;
        for(int j=0; j<squares[i].size(); j++) {
            temp.push_back(squares[i][j]);
        }

        temp  = temp + multiply(derived(temp),factor);
        for(int k=0; k<squares[i].size(); k++) {
            squares[i][k] = temp[k];
        }
    }


    for(int i=0;i<squares.size();i++) {
        for(int j=0; j<squares[i].size(); j++) {
            average += squares[i][j];
        }
        average = average/squares[i].size();
        y.push_back(average);
    }
}

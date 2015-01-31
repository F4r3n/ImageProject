#include "updater.h"

Updater::Updater(RenderArea *img, QLabel *inf) {
    this->img = img;
    this->inf = inf;
    running = true;
    type = 0;
}

void Updater::color(int t) {
    type = t;
    img->setType(t);
}

Updater::~Updater(){
    running = false;
    wait();
    terminate();
}

void Updater::run() {
    while(running) {
        this->msleep(100);
        QString s = img->getInfo();
        if(s!=0)
            inf->setText(s);
    }
}

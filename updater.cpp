#include "updater.h"

Updater::Updater(RenderArea *img, QLabel *inf) {
    this->img = img;
    this->inf = inf;
    running = true;
    type = 0;
}

void Updater::color(int t) {
    type = t;
}

Updater::~Updater(){
    running = false;
    wait();
    terminate();
}

void Updater::run() {
    while(running) {
        this->msleep(100);
        QString s = img->getInfo(type);
        if(s!=0)
            inf->setText(s);
    }
}

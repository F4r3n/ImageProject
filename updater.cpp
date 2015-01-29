#include "updater.h"

Updater::Updater(RenderArea *img, QLabel *inf) {
    this->img = img;
    this->inf = inf;
    running = true;
}

Updater::~Updater(){
    running = false;
    wait();
    terminate();
}

void Updater::run() {
    while(running) {
            QString s = img->getInfo();
            if(s!=0)
                inf->setText(s);
    }
}

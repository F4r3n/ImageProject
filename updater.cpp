#include "updater.h"

Updater::Updater(RenderArea *img, QLabel *inf) {
    this->img = img;
    this->inf = inf;
}

void Updater::run() {
    while(1) {
            QString s = img->getInfo();
            if(s!=0)
                inf->setText(s);
    }
}

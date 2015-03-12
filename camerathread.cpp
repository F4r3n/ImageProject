#include "camerathread.h"

CameraThread::CameraThread(QLabel *l, cv::VideoCapture s)
{
    _l = l;
    _s = s;
    running = true;
    compteur = 0;
}

QImage CameraThread::getImage() {
    return current;
}

void CameraThread::run() {
    int j=0;
    while(QDir(QString::number(j)).exists()){
        j++;
    }
    QDir().mkdir(QString::number(j));
    while(running) {
        this->msleep(150);
        cv::Mat cameraFrame;

        _s.read(cameraFrame);

        if(compteur>15){
            current = CameraWidget::Mat2QImage(cameraFrame);

            char f [20];
            sprintf(f,"file%03d.jpg",i);
            QString a = QString(QString::number(j)+"/"+f);
            if(current.save(a))
            {
            } else std::cout << "fail";
            _l->setPixmap(QPixmap::fromImage(current));
            i++;
        }
        compteur++;
    }
    _s.release();

}

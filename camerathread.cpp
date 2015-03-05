#include "camerathread.h"

CameraThread::CameraThread(QLabel *l, cv::VideoCapture s)
{
   _l = l;
   _s = s;
}

void CameraThread::run() {
    while(1) {
 this->msleep(100);
        cv::Mat cameraFrame;
        _s.read(cameraFrame);

        CameraWidget::putFrame(cameraFrame);
    }

}

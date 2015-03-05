#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H

#include "camerawidget.h"
#include <QThread>

class CameraThread : public QThread
{
    Q_OBJECT
public:
    explicit CameraThread(QLabel *l, cv::VideoCapture s);
    void run();

signals:

public slots:

private:
    QLabel *_l;
    cv::VideoCapture _s;

};

#endif // CAMERATHREAD_H

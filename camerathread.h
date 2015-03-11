#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H

#include "camerawidget.h"
#include <QThread>
#include <QDir>

class CameraThread : public QThread
{
    Q_OBJECT
public:
    explicit CameraThread(QLabel *l, cv::VideoCapture s);
    void run();
    QImage getImage();

signals:

public slots:

private:
    QLabel *_l;
    cv::VideoCapture _s;
    QImage current;
    int i=0;

};

#endif // CAMERATHREAD_H

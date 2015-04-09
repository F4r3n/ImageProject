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
    /*!
     * \brief Permet de lancer la webcam et le thread
     */
    void run();
    QImage getImage();
    bool running;

signals:

public slots:

private:
    QLabel *_l;
    cv::VideoCapture _s;
    QImage current;
    int i=0;
    int compteur;

};

#endif // CAMERATHREAD_H

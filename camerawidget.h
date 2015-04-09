#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QDialog>
#include <QApplication>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QDebug>
#include <cv.h>
#include <highgui.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "camerathread.h"


class CameraThread;

class CameraWidget : public QDialog
{
    Q_OBJECT
public:
    CameraWidget(QWidget *parent = 0);
    ~CameraWidget(void);
    QPixmap toPixmap(IplImage *);
    void putFrame(cv::Mat );
    static QImage Mat2QImage(cv::Mat const& src);
    cv::VideoCapture getStream();
    QLabel *getLabel();
    void setLabel(QLabel *l);



signals:

public slots:
    void displayWebcam();
    void aboutToclose();



private:
    QLabel *m_imageLabel;
    CameraThread *th;
    QVBoxLayout *m_layout;
    QImage m_image;
    CvCapture *capture;
    IplImage *image;
    cv::VideoCapture stream1;
    QPushButton *goButton;
    cv::Mat matImage;
    bool running;


};

#endif // CAMERAWIDGET_H

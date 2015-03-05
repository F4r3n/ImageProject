#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QDialog>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <cv.h>
#include <highgui.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "camerathread.h"
#include <QDebug>

class CameraThread;
class CameraWidget : public QDialog
{
    Q_OBJECT
public:
    CameraWidget(QWidget *parent = 0);
    ~CameraWidget(void);
    QPixmap toPixmap(IplImage *);
    static void putFrame(cv::Mat );
  static  QImage Mat2QImage(cv::Mat const& src);
    cv::VideoCapture getStream();
    QLabel *getLabel();
    void setLabel(QLabel *l);


signals:

public slots:
    void displayWebcam();



private:
   static QLabel *m_imageLabel;
    QVBoxLayout *m_layout;
    QImage m_image;
    CvCapture *capture;
    IplImage *image;
    cv::VideoCapture stream1;
    QPushButton *goButton;
    CameraThread *th;


};

#endif // CAMERAWIDGET_H

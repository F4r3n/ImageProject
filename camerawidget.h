#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QDialog>
#include <QLabel>
#include <QLayout>
#include <cv.h>
#include <highgui.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

class CameraWidget : public QDialog
{
    Q_OBJECT
public:
    CameraWidget(QWidget *parent = 0);
    ~CameraWidget(void);
    QPixmap toPixmap(IplImage *);
    void putFrame(IplImage *);
    void displayWebcam();
    QImage Mat2QImage(cv::Mat const& src);

signals:

public slots:


private:
    QLabel *m_imageLabel;
    QVBoxLayout *m_layout;
    QImage m_image;
    CvCapture *capture;
    IplImage *image;
    cv::VideoCapture stream1;

};

#endif // CAMERAWIDGET_H

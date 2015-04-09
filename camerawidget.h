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
    /*!
     * \brief Permet une conversion de IplImage vers QPixmap
     * \return
     */
    QPixmap toPixmap(IplImage *);
    void putFrame(cv::Mat );
    /*!
     * \brief Permet une conversion d'une image au format cv::Mat vers une QImage
     * \param src
     * \return
     */
    static QImage Mat2QImage(cv::Mat const& src);
    /*!
     * \brief Permet d'obtenir le steam de la vidéo
     * \return
     */
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

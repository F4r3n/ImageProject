#include "camerawidget.h"

CameraWidget::CameraWidget(QWidget *parent)
    : QDialog(parent)
{
    m_layout = new QVBoxLayout;
    m_imageLabel = new QLabel;
    QImage dummy(100, 100, QImage::Format_RGB32);
    m_image = dummy;
    m_layout->addWidget(m_imageLabel);
    for (int x = 0; x < 100; x ++)
        for (int y =0; y < 100; y++)
            m_image.setPixel(x,y,qRgb(x, y, y));
    m_imageLabel->setPixmap(QPixmap::fromImage(m_image));
    setLayout(m_layout);

    stream1 =cv::VideoCapture(0);

    if (!stream1.isOpened()) { //check if video device has been initialised
        std::cout << "cannot open camera";
    }
    //displayWebcam();
}

QImage CameraWidget::Mat2QImage(cv::Mat const& src)
{
     cv::Mat temp; // make the same cv::Mat
     cvtColor(src, temp,CV_BGR2RGB); // cvtColor Makes a copt, that what i need
     QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
     dest.bits(); // enforce deep copy, see documentation
     // of QImage::QImage ( const uchar * data, int width, int height, Format format )
     return dest;
}

void CameraWidget::displayWebcam() {
    while(1) {
        cv::Mat cameraFrame;
        stream1.read(cameraFrame);
        m_imageLabel->setPixmap(QPixmap::fromImage(Mat2QImage(cameraFrame)));


    }

}


CameraWidget::~CameraWidget(void)
{
}
void CameraWidget::putFrame(IplImage *image)
{
    m_imageLabel->setPixmap(toPixmap(image));
}
QPixmap CameraWidget::toPixmap(IplImage *cvimage) {
    int cvIndex, cvLineStart;
    switch (cvimage->depth) {
    case IPL_DEPTH_8U:
        switch (cvimage->nChannels) {
        case 3:
            if ( (cvimage->width != m_image.width()) || (cvimage->height != m_image.height()) ) {
                QImage temp(cvimage->width, cvimage->height, QImage::Format_RGB32);
                m_image = temp;
            }
            cvIndex = 0; cvLineStart = 0;
            for (int y = 0; y < cvimage->height; y++) {
                unsigned char red,green,blue;
                cvIndex = cvLineStart;
                for (int x = 0; x < cvimage->width; x++) {
                    red = cvimage->imageData[cvIndex+2];
                    green = cvimage->imageData[cvIndex+1];
                    blue = cvimage->imageData[cvIndex+0];
                    m_image.setPixel(x,y,qRgb(red, green, blue));
                    cvIndex += 3;
                }
                cvLineStart += cvimage->widthStep;
            }
            break;
        default:
            qWarning("This number of channels is not supported\n");
            break;
        }
        break;
    default:
        qWarning("This type of IplImage is not implemented in QOpenCVWidget\n");
        break;
    }
    return QPixmap::fromImage(m_image);
}

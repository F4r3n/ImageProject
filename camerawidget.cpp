#include "camerawidget.h"


CameraWidget::CameraWidget(QWidget *parent)
    : QDialog(parent)
{
    m_imageLabel = new QLabel;
    m_layout = new QVBoxLayout;
    goButton = new QPushButton("Go");
    QImage dummy(100, 100, QImage::Format_RGB32);
    m_image = dummy;
    m_layout->addWidget(m_imageLabel);
    m_layout->addWidget(goButton);
    for (int x = 0; x < 100; x ++)
        for (int y =0; y < 100; y++)
            m_image.setPixel(x,y,qRgb(x, y, y));
    m_imageLabel->setPixmap(QPixmap::fromImage(m_image));
    setLayout(m_layout);
    running = false;



    connect(goButton,SIGNAL(clicked()),this,SLOT(displayWebcam()));
}

QLabel* CameraWidget::getLabel() {
    return m_imageLabel;
}

cv::VideoCapture CameraWidget::getStream() {
    return stream1;
}

void CameraWidget::setLabel(QLabel *l) {
    m_imageLabel = l;
}

QImage CameraWidget::Mat2QImage(cv::Mat const& src)
{
    cv::Mat temp;
    cvtColor(src, temp,CV_BGR2RGB);
    QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    dest.bits();
    return dest;
}

void CameraWidget::aboutToclose() {
    stream1.release();
    th->running = false;
    this->close();
}

void CameraWidget::displayWebcam() {
    goButton->setText("Quitter");
    disconnect(goButton);
    connect(goButton,SIGNAL(clicked()),this,SLOT(aboutToclose()));

    if(!running) {
        stream1 =cv::VideoCapture(0);
        if (!stream1.isOpened()) {
            std::cout << "cannot open camera";
        }
        th = new CameraThread(m_imageLabel,stream1);

        th->start();
    }
    running = true;

}


CameraWidget::~CameraWidget(void)
{
}
void CameraWidget::putFrame(cv::Mat image)
{
    QImage i = CameraWidget::Mat2QImage(image);

    m_imageLabel->setPixmap(QPixmap::fromImage(i));
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

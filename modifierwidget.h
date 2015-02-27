#ifndef MODIFIERWIDGET_H
#define MODIFIERWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QSlider>
#include <QGridLayout>
#include <QImage>
#include <QPushButton>
#include <vector>
#include <cv.h>
#include <highgui.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "labelimage.h"
using namespace cv;

class ModifierWidget : public QWidget
{
    Q_OBJECT
private:
    int getSign(int a);

public:
    explicit ModifierWidget(LabelImage *parent = 0);
    void setGray(QImage &img);
    void setBorderX(QImage &img);
    void setGaussianBlur(QImage &image);
    float **kernelBox(int r);
    float computePixelBox(QImage &img, float **box,int x,int y,int n);
    void setCLTBlur(QImage &img,int n);
    void saveImage(const QImage &img);
    void setEdgeOpenCV(QImage &img);
    void CannyThreshold(int, void*);
    Mat qimage_to_mat_cpy(QImage const &img, int format);
    QImage Mat2QImage(Mat const& src);
    Mat QImage2Mat(QImage const& src);




signals:

public slots:
    void toGray(bool c);
    void toBlur(bool c);
    void toEdge(bool c);
    void resetImage();
    void toBlurCLT(bool c);

private:

    LabelImage *labelImage;
    QCheckBox *grayBox;
    QCheckBox *edgeBox;
    QCheckBox *smoothBox;
    QCheckBox *cltBox;
    QSlider *smoothSlider;
    QImage img;
    QImage beforeImg;
    QPushButton *resetButton;
    std::vector<QCheckBox*> tabBox;
    Mat src, src_gray;
    Mat dst, detected_edges;

    int edgeThresh = 1;
    int lowThreshold;
    int const max_lowThreshold = 100;
    int ratio = 3;
    int kernel_size = 3;


};

#endif // MODIFIERWIDGET_H

#ifndef MODIFIERWIDGET_H
#define MODIFIERWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QSlider>
#include <QGridLayout>
#include <QImage>
#include "labelimage.h"

class ModifierWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ModifierWidget(LabelImage *parent = 0);

signals:

public slots:

private:
    LabelImage *labelImage;
    QCheckBox *grayBox;
    QCheckBox *edgeBox;
    QCheckBox *smoothBox;
    QSlider *smoothSlider;
    QImage *img;

};

#endif // MODIFIERWIDGET_H

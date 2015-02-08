#include "modifierwidget.h"

ModifierWidget::ModifierWidget(LabelImage *parent)
{
    labelImage = parent;
    QGridLayout *gr = new QGridLayout();
    setLayout(gr);
    grayBox = new QCheckBox("Gray");
    edgeBox = new QCheckBox("Edge");
    smoothBox = new QCheckBox("smooth");

    smoothSlider = new QSlider();
    gr->addWidget(grayBox,0,0);
    gr->addWidget(edgeBox,0,1);
    gr->addWidget(smoothSlider,1,0);
    gr->addWidget(smoothBox,1,1);

    connect(smoothBox,SIGNAL(toggled(bool)),smoothSlider,SLOT(setDisabled(bool)));
}

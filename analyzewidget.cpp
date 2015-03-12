#include "analyzewidget.h"

AnalyzeWidget::AnalyzeWidget(QWidget *parent, CalcWidget *calc) :
    QWidget(parent)
{
    QGridLayout *grid = new QGridLayout();
    setLayout(grid);

    QRadioButton *analyze = new QRadioButton("Analyze");
    analyze->setChecked(false);
    QRadioButton *analyzeColor = new QRadioButton("Analyze with Color");
    analyzeColor->setChecked(true);

    QButtonGroup *btnGroup = new QButtonGroup(this);
    btnGroup->addButton(analyze);
    btnGroup->addButton(analyzeColor);

    grid->addWidget(analyze);
    grid->addWidget(analyzeColor);

    connect(btnGroup,SIGNAL(buttonClicked(int)),calc,SLOT(optionCalc(int)));
}

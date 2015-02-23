#ifndef ANALYZEWIDGET_H
#define ANALYZEWIDGET_H

#include <QWidget>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGridLayout>
#include "calcwidget.h"

class AnalyzeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AnalyzeWidget(QWidget *parent, CalcWidget *calc);

signals:

public slots:

};

#endif // ANALYZEWIDGET_H

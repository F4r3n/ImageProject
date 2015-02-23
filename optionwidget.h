#ifndef OPTIONWIDGET_H
#define OPTIONWIDGET_H

#include <QTabWidget>
#include "calcwidget.h"
#include "modifierwidget.h"
#include "analyzewidget.h"

class OptionWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit OptionWidget(LabelImage *parent);
    CalcWidget *getCalc();
    ModifierWidget *getModif();

signals:

public slots:
private:
    CalcWidget *calc;
    ModifierWidget *modif;
    AnalyzeWidget *analyze;
};

#endif // OPTIONWIDGET_H

#ifndef OPTIONWIDGET_H
#define OPTIONWIDGET_H

#include <QTabWidget>
#include "calcwidget.h"
#include "modifierwidget.h"

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

};

#endif // OPTIONWIDGET_H

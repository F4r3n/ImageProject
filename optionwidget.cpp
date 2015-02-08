#include "optionwidget.h"

OptionWidget::OptionWidget(LabelImage *parent)
{
    calc = new CalcWidget(parent);
    modif = new ModifierWidget(parent);
    addTab(calc,"Calcul");
    addTab(modif,"Options");
}

CalcWidget *OptionWidget::getCalc() {
    return calc;
}

ModifierWidget *OptionWidget::getModif() {
    return modif;
}



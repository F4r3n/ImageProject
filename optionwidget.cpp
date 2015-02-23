#include "optionwidget.h"

OptionWidget::OptionWidget(LabelImage *parent)
{
    calc = new CalcWidget(parent);
    modif = new ModifierWidget(parent);
    analyze = new AnalyzeWidget(parent,calc);

    addTab(calc,"Calcul");
    addTab(analyze,"Analyze");
    addTab(modif,"Options");
}

CalcWidget *OptionWidget::getCalc() {
    return calc;
}

ModifierWidget *OptionWidget::getModif() {
    return modif;
}



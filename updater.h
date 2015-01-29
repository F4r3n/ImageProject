#ifndef UPDATER_H
#define UPDATER_H

#include <QThread>
#include <QWidget>
#include <QLabel>
#include <QDebug>
#include "renderarea.h"

class Updater : public QThread
{
    Q_OBJECT
public:
    Updater(RenderArea *img,QLabel *inf);
    void run();
    bool running;

signals:

public slots:

private:
    QLabel *inf;
    RenderArea *img;
};

#endif // UPDATER_H

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
    ~Updater();
    bool running;

signals:

public slots:
    void color(int t);

private:
    QLabel *inf;
    RenderArea *img;
    int type;
};

#endif // UPDATER_H

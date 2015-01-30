#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include <QGridLayout>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QFileDialog>
#include <QImage>
#include <QApplication>
#include "updater.h"
#include "spc.h"
#include "renderarea.h"

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    void createMenu();
    void createAction();
    void setInfoPixel(QString string);
    ~Window();

signals:
    void clicked(int a);

public slots:
    void loadFile();
    void quitMyApp();
    void changeColor();

private:
    RenderArea *render;
    QPushButton *changeSpaceColor;
    QComboBox *spaceColorList;
    QLabel *info;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
    QMenu *helpMenu;
    QAction *loadAct;
    QAction *saveAct;
    Updater *up;
    int type;
};

#endif // WINDOW_H

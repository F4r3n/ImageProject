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

public slots:
    void loadFile();
    void quitMyApp();

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
};

#endif // WINDOW_H

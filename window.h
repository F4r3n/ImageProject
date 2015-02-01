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
#include <QUrl>
#include <vector>
#include <QProcess>
#include <QMessageBox>
#include "updater.h"
#include "spc.h"
#include "renderarea.h"


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
    void loadVideo();
    void displayAbout();

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
    QAction *imageAct;
    QAction *aboutAct;
    Updater *up;
    std::vector<QImage> images;
    int type;
};

#endif // WINDOW_H

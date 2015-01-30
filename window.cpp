#include "window.h"
#include <iostream>
Window::Window(QWidget *parent) :QMainWindow(parent)
{
    QWidget *panel = new QWidget();
    render = new RenderArea();

    setCentralWidget(panel);
    changeSpaceColor = new QPushButton("Change Color");
    spaceColorList = new QComboBox();
    info =new QLabel("Info");
    spaceColorList->addItem("RGB");
    spaceColorList->addItem("HSL");
    spaceColorList->addItem("HSV");


    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(3, 1);
    mainLayout->addWidget(render,0,0,1,4);
    mainLayout->addWidget(changeSpaceColor,2,0,Qt::AlignRight);
    mainLayout->addWidget(spaceColorList,2,1,Qt::AlignRight);
    mainLayout->addWidget(info,2,2,Qt::AlignRight);

    createAction();
    createMenu();
    panel->setLayout(mainLayout);
    up = new Updater(render,info);
    up->start();
   connect(qApp,SIGNAL(aboutToQuit()),this,SLOT(quitMyApp()));
   connect(changeSpaceColor,SIGNAL(clicked()),this,SLOT(changeColor()));
   connect(this,SIGNAL(clicked(int)),up,SLOT(color(int)));


}

void Window::quitMyApp() {
    delete up;
}


void Window::changeColor() {
    type = spaceColorList->currentIndex();
    emit clicked(type);
}

void Window::loadFile() {
    QString str = QFileDialog::getOpenFileName(this, tr("Open File"),
                                 "",
                                 tr("Files (*.*)"));
    QImage img;
    img.load(str.toUtf8().constData());
    render->setImage(&img);

}


void Window::createAction(){
    loadAct = new QAction("Load",this);
    connect(loadAct,SIGNAL(triggered()),SLOT(loadFile()));

}

void Window::createMenu() {
    fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction(loadAct);
    //fileMenu->addAction(saveAct);
}

Window::~Window()
{

}

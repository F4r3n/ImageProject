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
    spaceColorList->addItem("YUV");


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

}

void Window::quitMyApp() {
    up->terminate(); //Thread didn't exit in time, probably deadlocked, terminate it!
     up->wait(); //   up->
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
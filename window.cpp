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
    spaceColorList->addItem("LI");
    spaceColorList->addItem("HUE");


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
    QString str = QFileDialog::getExistingDirectory(this, tr("Open File"));
    if(str.isEmpty()) return;

    QDir export_folder(str);
    export_folder.setNameFilters(QStringList()<<"*.jpeg" << "*.png" << "*.jpg");
    export_folder.setSorting(QDir::LocaleAware);
    QStringList fileList = export_folder.entryList();

    images.clear();
    for(QString l : fileList){
        QImage img;
        qDebug() << l;
        img.load(str+"/"+l);
        images.push_back(img);
    }

    //  img.load(str.toUtf8().constData());
    render->setImages(&images);

}

void Window::loadVideo() {
    QString str = QFileDialog::getOpenFileName(this,
                                               tr("Open Video"),
                                               tr("Video Files (*.mp4 )"));

    if(str.isEmpty()) return;

    QProcess *p = new QProcess();
    QFileInfo f(str);
    QString path = f.absolutePath();
    p->start("sh",QStringList() << "image.sh" << str.toUtf8() << path.toUtf8());
    p->waitForStarted();

}


void Window::createAction(){
    loadAct = new QAction("Load",this);
    imageAct = new QAction("Create images",this);
    aboutAct = new QAction("About",this);

    connect(loadAct,SIGNAL(triggered()),SLOT(loadFile()));
    connect(imageAct,SIGNAL(triggered()),SLOT(loadVideo()));
    connect(aboutAct,SIGNAL(triggered()),SLOT(displayAbout()));
}

void Window::displayAbout() {
    QMessageBox msgBox;
     msgBox.setText("This software is based on Qt 5.2 and uses QCustomPlot \n Made by Kotulski Guillaume");
     msgBox.exec();
}

void Window::createMenu() {
    fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction(loadAct);
    fileMenu->addAction(imageAct);

    helpMenu = menuBar()->addMenu("Help");
    helpMenu->addAction(aboutAct);
}

Window::~Window()
{

}

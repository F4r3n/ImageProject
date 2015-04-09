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

    cameraButton = new QPushButton("Camera");
    cam = new CameraWidget(this);
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(3, 1);
    mainLayout->addWidget(cameraButton,2,0,Qt::AlignRight);
    mainLayout->addWidget(render,0,0,1,4);
    mainLayout->addWidget(changeSpaceColor,2,1,Qt::AlignRight);
    mainLayout->addWidget(spaceColorList,2,2,Qt::AlignRight);
    mainLayout->addWidget(info,2,3,Qt::AlignRight);

    createAction();
    createMenu();
    panel->setLayout(mainLayout);
    up = new Updater(render,info);
    up->start();
    connect(qApp,SIGNAL(aboutToQuit()),this,SLOT(quitMyApp()));
    connect(changeSpaceColor,SIGNAL(clicked()),this,SLOT(changeColor()));
    connect(this,SIGNAL(clicked(int)),up,SLOT(color(int)));
    connect(cameraButton,SIGNAL(clicked()),this,SLOT(showCam()));
    isRectAuto = true;
}

void Window::showCam() {
    cam->show();
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

    render->setImages(&images);
    if(isRectAuto) {
        render->createRect();
    }
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
    autoRect = new QAction("Auto rect",this);
    autoRect->setCheckable(true);
    autoRect->setChecked(true);

    connect(loadAct,SIGNAL(triggered()),SLOT(loadFile()));
    connect(imageAct,SIGNAL(triggered()),SLOT(loadVideo()));
    connect(aboutAct,SIGNAL(triggered()),SLOT(displayAbout()));
    connect(autoRect,SIGNAL(triggered()),SLOT(handleRect()));
}

void Window::handleRect() {
    if(autoRect->isChecked()) {
        isRectAuto = true;
    } else {
        isRectAuto = false;
    }
}

void Window::displayAbout() {
    QMessageBox msgBox;
     msgBox.setText("This software is based on Qt 5.2 and uses QCustomPlot \n Made by Kotulski Guillaume and Vimont ludovic");
     msgBox.exec();
}

void Window::createMenu() {
    fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction(loadAct);
    fileMenu->addAction(imageAct);

    optionMenu = menuBar()->addMenu("Options");
    optionMenu->addAction(autoRect);

    helpMenu = menuBar()->addMenu("Help");
    helpMenu->addAction(aboutAct);
}

Window::~Window()
{

}

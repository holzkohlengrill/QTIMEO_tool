#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <QPushButton>

#include "qtimeoGui.h"

MainWindow::MainWindow(QWidget *parent) {
  tabWidget = new QTabWidget;
  // create Tabs:
  tabCapture = new QWidget;
  tabImgConvert = new QWidget;
  tabCamSetup = new QWidget;

  tabWidget->setTabPosition(QTabWidget::North);

  // Capture tab content:
  labelCamera  = new QLabel;
  comboBoxCamera = new QComboBox;
  imageLeft = new QLabel;
  imageRight = new QLabel;
  startStopCapButton = new QPushButton;
  cameraComand = new QHBoxLayout;
  cameraComand->addWidget(labelCamera);
  cameraComand->addWidget(comboBoxCamera);
  cameraComand->addWidget(startStopCapButton);

  imageLeft->setFixedHeight(200);
  imageRight->setFixedHeight(200);
  // testimage:
  QPixmap imgleft("/home/marcel/pinkpanther.jpg");
  QPixmap imgright("/home/marcel/pinkpanther.jpg");

//  int w = imageLeft->width();
//  int h = imageLeft->height();

  imageLeft->setScaledContents(true);
  imageRight->setScaledContents(true);
  imageLeft->setPixmap(imgleft.scaled(this->width(),  this->height(), Qt::KeepAspectRatio));
  imageRight->setPixmap(imgleft.scaled(this->width(),  this->height(), Qt::KeepAspectRatio));
  //imageLeft->setPixmap(imgleft);
  //imageRight->setPixmap(imgright);
  //end:testimage
  imagePreview = new QHBoxLayout;
  imagePreview->addWidget(imageLeft);
  imagePreview->addWidget(imageRight);

  captureMain = new QVBoxLayout;
  captureMain->addLayout(cameraComand);
  captureMain->addLayout(imagePreview);

  tabCapture->setLayout(captureMain);

  // Add tabs:
  tabWidget->addTab(tabCapture, "Capture");
  tabWidget->addTab(tabImgConvert, "Convert Video to Image Sequence");
  tabWidget->addTab(tabCamSetup, "Camera Setup");

  tabWidget->show();

// -----------------------------------------------------------------------------------------------------
//  QMainWindow *window = new QMainWindow;
//  window->setWindowTitle("QTIMEO Tool");
//  window->resize(800, 300);

//  QWidget *centralWidget = new QWidget(window);
//  QTabWidget *mainTabs = new QTabWidget(centralWidget);
//  mainTabs->setTabPosition(QTabWidget::North);


//  mainTabs->addTab(new QWidget, "Capture");
//  mainTabs->addTab(new QWidget, "Convert from ImgSeq");
//  mainTabs->addTab(new QWidget, "Setup Cameras");

//  window->setCentralWidget(mainTabs);
//  window->show();
}

void MainWindow::keepAspectRatio() {
  imageLeft->setPixmap(imgleft.scaled(this->width(),  this->height(), Qt::KeepAspectRatio));
  imageRight->setPixmap(imgleft.scaled(this->width(),  this->height(), Qt::KeepAspectRatio));
}

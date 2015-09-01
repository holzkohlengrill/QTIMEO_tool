#include <QApplication>
#include <QMainWindow>
#include <QTabWidget>

#include "qtimeoGui.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
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

  MainWindow *centralWidget= new MainWindow;
  MainWindow::connect(centralWidget, SIGNAL()
//  window->setCentralWidget(centralWidget);
//  window->show();

  return a.exec();
//  delete window;
}

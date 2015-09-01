#ifndef QTIMEOGUI_H
#define QTIMEOGUI_H

#include <QTabWidget>

// forward declarations
class QLabel;
class QComboBox;
class QHBoxLayout;
class QPixmap;
class QVBoxLayout;
class QPushButton;

class MainWindow : public QTabWidget {
  Q_OBJECT

public:
  MainWindow(QWidget * parent = 0);
  ~MainWindow(){
  }

signals:
  bool startCapture();
  bool stopCapture();


private slots:
  void keepAspectRatio();

private:
  QTabWidget *tabWidget;
  // tabs:
  QWidget *tabCapture;
  QWidget *tabImgConvert;
  QWidget *tabCamSetup;

  // Capture tab:
  QLabel *labelCamera;
  QComboBox *comboBoxCamera;
  QLabel *imageLeft;
  QLabel *imageRight;
  QPushButton *startStopCapButton;
  QHBoxLayout *imagePreview;
  QHBoxLayout *cameraComand;
  QPixmap *imageLeftTest;
  QPixmap *imageRightTest;
  QVBoxLayout *captureMain;

  //QProgressBar *progBar;
  //or:
  //QProgressDialog *progDialog;
};

#endif // QTIMEOGUI_H

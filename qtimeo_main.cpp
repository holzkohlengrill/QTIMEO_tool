#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>            // for setw(), setfill(), etc.
#include <tuple>                 // for std::tie

#include <chrono>             // for std::this_thread::sleep_for()
#include <thread>             // for std::this_thread::sleep_for()
//#include <ctime>              // for asctime, difftime, time, ...

//TODO: use Qt or other platform independent 'tool' for folder creation
#include <sys/types.h>      // for folder cration in ubuntu
#include <sys/stat.h>         // for folder cration in ubuntu
#include <unistd.h>            // for folder cration in ubuntu

#include <m3api/xiApi.h>    // XIMEA camera API

#include "imeovid.h"

////############## VARIABLES #######################

////TODO: remove global variables & use classes
////cv::Mat frameShow;
//cv::Mat frame, frame2;

////############## CLASSES ########################
//class imeoVid imeoVid;

////############## SETTINGS ########################

////############## FUNCTION PROTOTYPES ###############

// program control
bool keyhandler();
//// folder creation
void createSavesFolder(std::string filename);
////cv::Mat retrieveFrame(XI_IMG image);
////cv::Mat convXI_IMG2cvMat(XI_IMG xiImage);

/* test to use opencv implementation
 *
////cv::Mat convXI_IMG2cvMat(XI_IMG xiImage){
////  cv::Mat cvimg;
////  switch( xiImage.frm){
////    case XI_MONO8       :
////    case XI_RAW8        : memcpy( cvimg.data, xiImage.bp, xiImage.width*xiImage.height); break;
////    case XI_MONO16      :
////    case XI_RAW16       : memcpy( cvimg.data, xiImage.bp, xiImage.width*xiImage.height*sizeof(WORD)); break;
////    case XI_RGB24       :
////    case XI_RGB_PLANAR  : memcpy( cvimg.data, xiImage.bp, xiImage.width*xiImage.height*3); break;
////    case XI_RGB32       : memcpy( cvimg.data, xiImage.bp, xiImage.width*xiImage.height*4); break;
////    default: break;
////    }
////  // evt. neues mat objekt erstellen und kopieren
////  return cvimg;
////}

////cv::Mat retrieveFrame(XI_IMG image){
////  //XI_IMG image;
////  IplImage* frame;
////  // update cvImage after format has changed
////  //resetCvImage();
////  // copy pixel data
////  switch( image.frm)
////    {
////    case XI_MONO8       :
////    case XI_RAW8        : memcpy( frame->imageData, image.bp, image.width*image.height); break;
////    case XI_MONO16      :
////    case XI_RAW16       : memcpy( frame->imageData, image.bp, image.width*image.height*sizeof(WORD)); break;
////    case XI_RGB24       :
////    case XI_RGB_PLANAR  : memcpy( frame->imageData, image.bp, image.width*image.height*3); break;
////    case XI_RGB32       : memcpy( frame->imageData, image.bp, image.width*image.height*4); break;
////    default: break;
////    }
////  cv::Mat frameMat = cv::cvarrToMat(frame);
////  return frameMat;
////}
///
/// */

CamManager manager;
std::pair<cv::Mat, cv::Mat> stereoCapture(const std::string &camName1, const std::string &camName2);
void showText(const std::string &text, cv::Mat &img, const int &pos);
void camInit(const std::string &camName1, const std::string &camName2);

int main() {
  manager.add("cam1", 1);
  manager.add("cam2", 0);
  camInit("cam1", "cam2");
  VimeoControl vCtrl;

  while(1) {
      std::pair<cv::Mat, cv::Mat> stereoPair = stereoCapture("cam1", "cam2");
      cv::imshow("cam1", stereoPair.first);
      //cv::imshow("cam2", stereoPair.second);
      if(!vCtrl.keyhandler())    // uses cv::waitKey(2) >> needed for cv::imshow()
        return 0;
    }
  return 0;
}


// "Warming up" - avoids black image at the very beginning of each capture
void camInit(const std::string &camName1, const std::string &camName2) { //TODO: use stereoref for stereocam ID's
  CamMono cam1 = manager.getCam(camName1);
  //CamMono cam2 = manager.getCam(camName2);
  cam1.grab();
  //cam2.grab();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << "\t(info) Init done..." << std::endl;
}

std::pair<cv::Mat, cv::Mat> stereoCapture(const std::string &camName1, const std::string &camName2) {   //TODO: use stereoref for stereocam ID's
  CamMono cam1 = manager.getCam(camName1);
  CamMono cam2 = manager.getCam(camName2);
  cv::Mat img1, img2;

  /********************************************************************************* opencv VideoCapture::read() = .grab() + .retrieve(...) implementation
    // opencv read implementation:

    bool VideoCapture::read(OutputArray image)
    {
        if(grab())
            retrieve(image);
        else
            image.release();
        return !image.empty();
    }
  /**********************************************************************************/

  if(cam1.grab() /*&& cam2.grab() */) {
      cam1.retrieve(img1, 0);
      //cam2.retrieve(img2, 0);
    }

  /********************************************************************************* time measure
     // time measure
  //  double t1 = (double)cv::getTickCount();
  //  // do something
  //  t1 = ((double)cv::getTickCount() - t1)/cv::getTickFrequency();
  //  std::string tmp2 =  std::to_string(t1);                      // cout time measure
  //  std::cout << "time : " << tmp2 << std::endl;      // ...
  /**********************************************************************************/
  return std::make_pair(img1, img2);
}

void showText(const std::string &text, cv::Mat &img, const int &pos) {
  int baseline = 0;
  const int tFont = cv::FONT_HERSHEY_SIMPLEX;
  const double tScale = 0.7;
  const cv::Scalar tColour(255, 0, 60);
  const int tLineType = cv::LineTypes::LINE_AA;
  const int tThickness = 1;
  cv::Size textprop = cv::getTextSize(text, tFont, tScale, tThickness, &baseline);
  cv::Point tOrigin(static_cast<int>(img.cols/2), static_cast<int>(img.rows-textprop.height*pos*1.2));
  cv::putText(img, text, tOrigin, tFont, tScale, tColour, tThickness, tLineType, false);
}

void createSavesFolder(std::string filename){
  struct stat st = {0};
  if (stat(filename.c_str(), &st) == -1) {      // creating directory if not existing
      mkdir(filename.c_str(), 0700);
    }
}

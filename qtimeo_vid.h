#ifndef IMEOVID_H
#define IMEOVID_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>            // for setw(), setfill(), etc.
#include <tuple>
#include <utility>                // for make_pair
#include <unordered_map>
#include <m3api/xiApi.h>    // XIMEA camera API


class CamMono {
public:
  CamMono() {
  }
  CamMono(int camSlot) :  cam(camSlot), slot(camSlot), trigger(false) {

//     // XIMEA hardware trigger
//    HANDLE hmv;
//    xiOpenDevice(camSlot, &hmv);
//    xiStopAcquisition(hmv);
//    xiSetParamInt(hmv, XI_PRM_TRG_SOURCE, XI_TRG_EDGE_RISING);
//    xiSetParamInt(hmv, XI_PRM_GPI_SELECTOR, 1);
//    xiSetParamInt(hmv, XI_PRM_GPI_MODE, XI_GPI_TRIGGER);
//    xiStartAcquisition(hmv);
//    // >> is working!

  }
  ~CamMono(){
  }
  cv::Mat capture();
  bool grab();
  bool retrieve(cv::Mat &imgOut, const int &flag = 0);
  int getSlot() const;
  bool setProp(int propID, double value);
  double getProp(int propID);
  // returns the current trigger status >> true = ext hardware trigger enabled
  bool toggleExtTrigger();        // only implemented for XIMEA cameras

private:
  cv::VideoCapture cam;
  int slot;
  cv::Mat image;
  bool trigger;
};

/**********************************************************************************/

class CamManager {
public:
  // Adds a new camera which can later be called by its arbitrary user-predefined name (camName)
  void add(const std::string &camName, const int &camSlot);
  // Removes camera by name and returns their corresponding slot
  int remove(const std::string &camName);
  void addStereoRef(const std::string &camName1, const std::string &camName2);
  int getSlot(const std::string &name);
  CamMono getCam(const std::string &name);


  // contains all camera objects with its predefined names given by add()
  std::unordered_map<std::string, CamMono> camMonoMap;
  // mapping of stereo cameras - contains only correspondences; no camera objects
  std::unordered_map<std::string, std::string> stereoDefs;
private:

};

enum VimeoMode{
  EXIT         = 1 << 0,
  IMGCAP  = 1 << 1,
  VIDEXT   = 1 << 2,
  VIEW       = 1 << 3
};

class VimeoControl {
  friend class CamMono;
public:
  VimeoControl() : mode(VIEW) {
  }
  bool isSet(const VimeoMode &flagToCheck) const; // returns true if set
  bool keyhandler();
private:
  VimeoMode mode;
};

/**********************************************************************************/

//class MonoCam {
//public:
//  // constructor needed for inheritance
//  MonoCam() {
//  }
//  MonoCam(std::size_t id) {
//    setSlot(id);
//  }
//  ~MonoCam() {
//  }
//  cv::Mat Capture(const int camSlot);
//  std::string SaveCapture(const cv::Mat &image, const std::string &destPath = "../monoImgSeq/", const std::string &filePrefix = "img_");
//  void setSlot(const std::size_t &value);
//  std::size_t getSlot() const;

//private:
//  cv::Mat image;
//  std::size_t slot;
//};

///**********************************************************************************/

//class StereoCam : private MonoCam {
//public:
//  StereoCam() {
//  }
//  ~StereoCam() {
//  }

// std::tuple<cv::Mat, cv::Mat> Capture(const std::pair<const int, const int> &StereoRef);
// std::tuple<std::string, std::string> SaveCapture(const cv::Mat &image1, const cv::Mat &image2, const std::string &destPath = "../stereoImgSeq/");

//private:
// cv::Mat image1;
// cv::Mat image2;
//};

///**********************************************************************************/

//class CameraManager {
//public:
//  // create a new camera object
//  void create(const int &slot);
//  // delete a camera object
//  void purge(const int &slot);
//  // define stereo pair
//  void setStereo(const int &camID1, const int &camID2);
//  // returns slot of vector ID
//  int getSlotMono(const int &ID) const;
//  // returns a poir of stereo slot of vector ID
//  std::pair<int, int> getSlotStereo(const int &ID) const;
//  // returns a vector of all defined camera slots
//  std::vector<int> getMonoCams() const;
//  // returns a vector of all defined stereo camera slots as pairs
//  std::vector<std::pair<int, int>> getStereoDefs() const;

//  std::vector<MonoCam> camSlotList;

//private:
//  std::vector<std::pair<int, int>> stereoDefs;
//};

///**********************************************************************************/

//class imeoVid {
//public:
//  enum Mode{IMGCAP, VIDEXT, VIEW, EXIT} mode = VIEW;

//  // camera live view
//  void liveView(cv::Mat &outputFrame);
//  // saves images from camera live view
//  std::tuple <cv::Mat, std::size_t> imgcap();     // returns the current image and current frame number
//  // extracts an image sequence from a video
//  bool vidext();

//private:
//  size_t numbCams = 1;
//  // text overlay in live view [pos := positioning upwards as a multiple of textsize*1.2]
//  void showText(std::string text, cv::Mat &img, int pos);
//  // nomal capture
//  void capture(cv::Mat &img);
//  // capture for creating image sequences from videos >> esp. for vidext()
//  void capture(size_t &count, cv::Mat &img);
//};

///**********************************************************************************/

#endif // IMEOVID_H

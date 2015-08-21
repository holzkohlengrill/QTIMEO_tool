#include "imeovid.h"

//TODO: slots increment when new camera is added >> fix? >> evt. function "newCameraAdded" >> increment slot and camera name by 1

void CamManager::add(const std::string &camName, const int &camSlot) {
  camMonoMap.insert(std::make_pair(camName, CamMono(camSlot)));
}

/**********************************************************************************/

int CamManager::remove(const std::string &camName) {
  //  std::unordered_map<std::string, CamMono>::iterator iter = camMonoMap[camName];
  //  int delName = camMonoMap[camName].getSlot(iter->first);
  //  camMonoMap.erase(iter->first);
  //  return delName;
  CamMono tmp = camMonoMap[camName];
  int delName = tmp.getSlot();
  camMonoMap.erase(camName);
  std::cout << "[info] Camera " << camName << " at slot: " << delName << " closed" << std::endl;
  return delName;

  /*auto iter = camMonoMap.find(camName);
    if ( iter == camMonoMap.end() ){
        std::cerr << "Camera slot not found" << std::endl;
        return -1;
      }
    else {
        int delName = iter->second.getSlot();
        camMonoMap.erase(camName);
        return delName;
      } */
}

/**********************************************************************************/

void CamManager::addStereoRef(const std::string &camName1, const std::string &camName2) {
  stereoDefs.insert(std::make_pair(camName1, camName2));
}

/**********************************************************************************/

CamMono CamManager::getCam(const std::string &name) {
  CamMono cam = camMonoMap[name];
  return cam;
}

/**********************************************************************************/

int CamManager::getSlot(const std::string &name) {
  CamMono tmp = camMonoMap[name];
  return tmp.getSlot();
}

/**********************************************************************************/

cv::Mat CamMono::capture() {
  cam >> image;
  return image;
}

/**********************************************************************************/

int CamMono::getSlot() const {
  return slot;
}

/**********************************************************************************/

bool CamMono::grab() {
  bool success = cam.grab();
  return success;
}

/**********************************************************************************/

bool CamMono::retrieve(cv::Mat &imgOut, const int &flag) {
  bool success = cam.retrieve(imgOut, flag);
  return success;
}

/**********************************************************************************/

bool CamMono::setProp(int propID, double value) {
  return cam.set(propID, value);
}

/**********************************************************************************/

double CamMono::getProp(int propID) {
  return cam.get(propID);
}

/**********************************************************************************/

bool CamMono::toggleExtTrigger() {
  trigger = !trigger;
  HANDLE hmv;

  if(trigger) {
      // XIMEA external hardware trigger
      xiOpenDevice(slot, &hmv);
      xiStopAcquisition(hmv);
      xiSetParamInt(hmv, XI_PRM_TRG_SOURCE, XI_TRG_EDGE_RISING);
      xiSetParamInt(hmv, XI_PRM_GPI_SELECTOR, 1);
      xiSetParamInt(hmv, XI_PRM_GPI_MODE, XI_GPI_TRIGGER);
      xiStartAcquisition(hmv);
    } else {
      // enable XIMEA normal (not triggered) mode
      xiOpenDevice(slot, &hmv);
      xiStopAcquisition(hmv);
      xiSetParamInt(hmv, XI_PRM_TRG_SOURCE, XI_TRG_OFF);
      xiStartAcquisition(hmv);
    }
  return trigger;
}

/**********************************************************************************/

bool VimeoControl::isSet(const VimeoMode &flagToCheck) const {
  return (mode & flagToCheck) != 0;
}

/**********************************************************************************/

bool VimeoControl::keyhandler(){
  switch(cv::waitKey(2)){
    case 's' : mode = mode == IMGCAP ? VIEW : IMGCAP; break;
    case 'v' : mode = mode == VIDEXT ?  VIEW : VIDEXT; break;
    case 't' :
      {
      HANDLE hmv;
      static bool trigger = false;
      int slot = 1;
      trigger = !trigger;
      if(trigger) {
          // XIMEA external hardware trigger
          xiOpenDevice(slot, &hmv);
          xiStopAcquisition(hmv);
          xiSetParamInt(hmv, XI_PRM_TRG_SOURCE, XI_TRG_EDGE_RISING);
          xiSetParamInt(hmv, XI_PRM_GPI_SELECTOR, 1);
          xiSetParamInt(hmv, XI_PRM_GPI_MODE, XI_GPI_TRIGGER);
          xiStartAcquisition(hmv);
        } else {
          // enable XIMEA normal (not triggered) mode
          xiOpenDevice(slot, &hmv);
          xiStopAcquisition(hmv);
          xiSetParamInt(hmv, XI_PRM_TRG_SOURCE, XI_TRG_OFF);
          xiStartAcquisition(hmv);
        }
      }
      break;
    case 27 : std::cout << "\t(info) ESC key pressed by user" << std::endl; mode = EXIT; return(false); break;
    }
  return true;
}

/**********************************************************************************/

//void CameraManager::create(const int &slot) {
//  MonoCam tmp = MonoCam(slot);
//  camSlotList.push_back(tmp);
//}

///**********************************************************************************/

//void CameraManager::purge(const int &slot) {
//  camSlotList.erase(camSlotList.begin() + slot);
//}

///**********************************************************************************/

//void CameraManager::setStereo(const int &camID1, const int &camID2) {
//  stereoDefs.push_back(std::make_pair<int, int>(getSlotMono(camID1), getSlotMono(camID2)));
//}

///**********************************************************************************/

//int CameraManager::getSlotMono(const int &ID){
//  int slot = 0;// camSlotList[ID];
//  return slot;
//}

///**********************************************************************************/

//std::pair<int, int> CameraManager::getSlotStereo(const int &ID) const{
//  return std::make_pair<int, int>(stereoDefs[ID].first, stereoDefs[ID].second);
//}

///**********************************************************************************/

//std::vector<int> CameraManager::getMonoCams() const {
//  std::vector<int> slotList = camSlotList;
//  return slotList;
//}

///**********************************************************************************/

//std::vector<std::pair<int, int>> CameraManager::getStereoDefs() const{
//  std::vector<std::pair<int, int>> tmpStereoDefs = stereoDefs;
//  return tmpStereoDefs;
//}

///**********************************************************************************/

//cv::Mat MonoCam::Capture(const int camSlot) {
//  static cv::VideoCapture cam(camSlot);
//  cam >> image;
//  return image;
//}

///**********************************************************************************/

//std::string MonoCam::SaveCapture(const cv::Mat &image, const std::string &destPath, const std::string &filePrefix) {
//  static size_t currentPicID = 0;
//  std::stringstream filename;
//  filename << /* file prefix */ filePrefix << std::setw(5) << std::setfill('0') << std::to_string(currentPicID) << ".png";
//  std::stringstream msg;
//  msg << "File " << filename.str() << " saved!";
//  // saved in this directory
//  filename.str(destPath+filename.str());
//  std::string pathToFile = filename.str();
//  cv::imwrite(pathToFile, image);
//  currentPicID++;
//  return pathToFile;
//}

///**********************************************************************************/

//std::size_t MonoCam::getSlot() const {
//  return slot;
//}

///**********************************************************************************/

//void MonoCam::setSlot(const std::size_t &value) {
//  slot = value;
//}

///**********************************************************************************/

//std::tuple<cv::Mat, cv::Mat> StereoCam::Capture(const std::pair<const int, const int>& StereoRef) {
//  image1 = MonoCam.Capture(StereoRef.first);
//  image2 = MonoCam.Capture(StereoRef.second);
//  return make_tuple(image1, image2);
//}

///**********************************************************************************/

//std::tuple<std::string, std::string> StereoCam::SaveCapture(const cv::Mat &image1, const cv::Mat &image2, const std::string &destPath){
//  std::string pathToFile1 = MonoCam.SaveCapture(image1, destPath, "A_stereo");
//  std::string pathToFile2 = MonoCam.SaveCapture(image2, destPath, "B_stereo");
//  return make_tuple(pathToFile1, pathToFile2);
//}

///**********************************************************************************/

//void imeoVid::liveView(cv::Mat &outputFrame){
//  capture(outputFrame);
//  showText("Press 's' to start/stop recording", outputFrame, 4);
//  showText("Press 'v' to extract an img seq of a .mp4 video file", outputFrame, 3);
//  showText("Press 'ESC' to exit", outputFrame, 2);
//}

///**********************************************************************************/

//std::tuple <cv::Mat, std::size_t> imeoVid::imgcap(){     // returns the current image and current frame number
//  cv::Mat currentImg;
//  static size_t currentPicID = 0;
//  capture(currentImg);
//  cv::Mat frame = currentImg.clone();
//  std::stringstream filename;
//  filename << /* file prefix */ "img" << std::setw(5) << std::setfill('0') << std::to_string(currentPicID) << ".png";
//  std::stringstream msg;
//  msg << "File " << filename.str() << " saved!";
//  // saved in this directory
//  filename.str("../saves/"+filename.str());
//  cv::imwrite(filename.str(), frame);
//  showText(msg.str(), currentImg, 2);
//  currentPicID++;
//  return std::make_tuple(currentImg, currentPicID);
//}

///**********************************************************************************/

////void imeoVid::vidext(){
////  static size_t i = 0;
////  static size_t count = 0;
////  static cv::VideoCapture video("../dataset2.mp4");
////  static const size_t count_max = (video.get(CV_CAP_PROP_FRAME_COUNT)-1);

////  if(count >= count_max){
////      showText("Video extracting finished", frameShow, 2);
////      cv::waitKey(1000);
////      showText("Video extracting finished.", frameShow, 2);
////      cv::waitKey(1000);
////      showText("Video extracting finished..", frameShow, 2);
////      cv::waitKey(1000);
////      showText("Video extracting finished...", frameShow, 2);
////      cv::waitKey(1000);
////      showText("\n>> Starting livestream in 2 seconds...", frameShow, 2);
////      cv::waitKey(2000);
////      mode = VIEW;
////    } else{
////      capture(count, frame);
////      frameShow = frame.clone();

////      std::stringstream filename;
////      filename <<  /* file prefix */ "vid" << std::setw(5) << std::setfill('0') << std::to_string(count) << ".png";
////      std::stringstream msg;
////      msg << "File " << filename.str() << " saved!";
////      // saved in this directory
////      filename.str("../vid_extr2/"+filename.str());
////      count++;

////      cv::imwrite(filename.str(), frame);
////      showText(msg.str(), frameShow, 2);
////    }
////}

///**********************************************************************************/

//void imeoVid::showText(std::string text, cv::Mat &img, int pos){
//  int baseline = 0;
//  const int tFont = cv::FONT_HERSHEY_SIMPLEX;
//  const double tScale = 0.7;
//  const cv::Scalar tColour(255, 0, 60);
//  const int tLineType = cv::LineTypes::LINE_AA;
//  const int tThickness = 1;
//  cv::Size textprop = cv::getTextSize(text, tFont, tScale, tThickness, &baseline);
//  cv::Point tOrigin(static_cast<int>(img.cols/2), static_cast<int>(img.rows-textprop.height*pos*1.2));
//  cv::putText(img, text, tOrigin, tFont, tScale, tColour, tThickness, tLineType, false);
//}

///**********************************************************************************/

//void imeoVid::capture(cv::Mat &img){
//  switch(mode){
//    case VIEW :
//    case IMGCAP :
//      static cv::VideoCapture cap(0);
//      cap >> img;
//      break;
//    default : // do nothing
//      break;
//    }
//}

///**********************************************************************************/

//void imeoVid::capture(size_t &count, cv::Mat &img){
//  static cv::VideoCapture video("../dataset2.mp4");
//  video.set(CV_CAP_PROP_POS_FRAMES, count);
//  video.read(img);
//}

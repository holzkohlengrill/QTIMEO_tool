QT       += core
QT       += gui
QT       += multimedia
QT       += multimediawidgets
QT       += opengl
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cam-capture
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp \
    imeovid.cpp \
    capXIMEA.cpp

INCLUDEPATH += \
    /usr/local/include/opencv
    #/opt/XIMEA/


LIBS += \
    -lm3api \						# XIMEA API lib for linux
    -lopencv_core \
    -lopencv_imgproc \
    -lopencv_highgui \
    -lopencv_ml \
    -lopencv_video \
    -lopencv_features2d \
    -lopencv_calib3d \
    -lopencv_objdetect \
    -lopencv_imgcodecs \
#    -lopencv_contrib \     # for opencv < 3.0.0
#    -lopencv_legacy \     # for opencv < 3.0.0
    -lopencv_videoio \     # for opencv > 3.0.0
    -lopencv_flann

HEADERS += \
    imeovid.h \
    capXIMEA.h

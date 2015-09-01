#-------------------------------------------------
#
# Project created by QtCreator 2015-08-25T11:16:22
#
#-------------------------------------------------

QT       += \
	core \
	gui \


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtimeo
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp \
    qtimeovid.cpp \
    qtimeoGui.cpp

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
    qtimeovid.h \
    qtimeoGui.h

# Add more folders to ship with the application, here
TEMPLATE = app

QT      += quick network quickcontrols2
CONFIG  += c++11

TARGET = ES2

#debug日志信息
DEFINES += QT_MESSAGELOGCONTEXT

HEADERS +=        \
    mytcpsocket.h \
    filetool.h    \
    color.h

SOURCES += main.cpp \
    mytcpsocket.cpp \
    filetool.cpp    \
    color.cpp

RESOURCES +=

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =


RESOURCES += \
           qml.qrc


RC_FILE += es2.rc

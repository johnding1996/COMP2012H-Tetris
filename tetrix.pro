TEMPLATE = app
CONFIG += qt warn_on
TARGET = tetris
DESTDIR = bin
MOC_DIR = tmp
OBJECTS_DIR = obj
RES_DIR = resource
DEPENDPATH  += src include
INCLUDEPATH += include

HEADERS += include/tetrix_block.h \
           include/tetrix_frame.h  \
           include/tetrix_nextframe.h \
           include/tetrix_window.h
SOURCES += src/tetrix.cpp \
           src/tetrix_block.cpp \
           src/tetrix_frame.cpp \
           src/tetrix_nextframe.cpp \
           src/tetrix_window.cpp

QMAKE_POST_LINK= cp -r $${RES_DIR}/* $${DESTDIR}
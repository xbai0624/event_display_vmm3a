######################################################################
# Automatically generated by qmake (3.1) Thu Oct 22 17:42:53 2020
######################################################################

TEMPLATE = app
TARGET = main

CONFIG += Qt DEBUG c++11
QT += core gui widgets


MOC_DIR = moc
OBJECTS_DIR = obj

# ROOT and Local include and library
INCLUDEPATH += . ./include ${ROOTSYS}/include

LIBS += -L$(ROOTSYS)/lib -lCore -lRIO -lNet \
        -lHist -lGraf -lGraf3d -lGpad -lTree \
        -lRint -lPostscript -lMatrix -lPhysics \
        -lGui -lRGL

# dictionary
LIBS += -Ldict/ -lStlDict

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += include/QRootCanvas.h \
           include/QMainCanvas.h \
           include/Viewer.h \
           include/ComponentsSchematic.h \
           include/RootTree.h \
           include/Analyzer.h \
           include/Cluster.h \
           include/ValueType.h \
           include/Config.h \
           include/histos.hpp \

SOURCES += src/main.cpp \
           src/QRootCanvas.cpp \
           src/QMainCanvas.cpp \
           src/Viewer.cpp \
           src/ComponentsSchematic.cpp \
           src/RootTree.cpp \
           src/Analyzer.cpp \
           src/Cluster.cpp \
           src/ValueType.cpp \
           src/Config.cpp \

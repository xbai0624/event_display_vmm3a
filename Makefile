#############################################################################
# Makefile for building: main
# Generated by qmake (3.1) (Qt 5.9.7)
# Project:  event_display.pro
# Template: app
# Command: /usr/bin/qmake-qt5 -o Makefile event_display.pro
#############################################################################

MAKEFILE      = Makefile

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB
CFLAGS        = -pipe -O2 -g -pipe -Wall -Wp,-D_FORTIFY_SOURCE=2 -fexceptions -fstack-protector-strong --param=ssp-buffer-size=4 -grecord-gcc-switches -m64 -mtune=generic -O2 -D_REENTRANT -Wall -W -fPIC $(DEFINES)
CXXFLAGS      = -pipe -O2 -g -pipe -Wall -Wp,-D_FORTIFY_SOURCE=2 -fexceptions -fstack-protector-strong --param=ssp-buffer-size=4 -grecord-gcc-switches -m64 -mtune=generic -O2 -std=gnu++11 -D_REENTRANT -Wall -W -fPIC $(DEFINES)
INCPATH       = -I. -I. -Iinclude -I${ROOTSYS}/include -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -Imoc -isystem /usr/include/libdrm -I/usr/lib64/qt5/mkspecs/linux-g++
QMAKE         = /usr/bin/qmake-qt5
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = cp -f -R
QINSTALL      = /usr/bin/qmake-qt5 -install qinstall
QINSTALL_PROGRAM = /usr/bin/qmake-qt5 -install qinstall -exe
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
TAR           = tar -cf
COMPRESS      = gzip -9f
DISTNAME      = main1.0.0
DISTDIR = /home/vt/event_display_vmm3a/obj/main1.0.0
LINK          = g++
LFLAGS        = -Wl,-O1 -Wl,-z,relro
LIBS          = $(SUBLIBS) -L$(ROOTSYS)/lib -lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lGui -lRGL -Ldict/ -lStlDict -lQt5Widgets -lQt5Gui -lQt5Core -lGL -lpthread 
AR            = ar cqs
RANLIB        = 
SED           = sed
STRIP         = 

####### Output directory

OBJECTS_DIR   = obj/

####### Files

SOURCES       = src/main.cpp \
		src/QRootCanvas.cpp \
		src/QMainCanvas.cpp \
		src/Viewer.cpp \
		src/ComponentsSchematic.cpp \
		src/RootTree.cpp \
		src/Analyzer.cpp \
		src/Cluster.cpp \
		src/ValueType.cpp \
		src/Config.cpp moc/moc_QRootCanvas.cpp \
		moc/moc_QMainCanvas.cpp \
		moc/moc_Viewer.cpp \
		moc/moc_ComponentsSchematic.cpp
OBJECTS       = obj/main.o \
		obj/QRootCanvas.o \
		obj/QMainCanvas.o \
		obj/Viewer.o \
		obj/ComponentsSchematic.o \
		obj/RootTree.o \
		obj/Analyzer.o \
		obj/Cluster.o \
		obj/ValueType.o \
		obj/Config.o \
		obj/moc_QRootCanvas.o \
		obj/moc_QMainCanvas.o \
		obj/moc_Viewer.o \
		obj/moc_ComponentsSchematic.o
DIST          = /usr/lib64/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib64/qt5/mkspecs/common/unix.conf \
		/usr/lib64/qt5/mkspecs/common/linux.conf \
		/usr/lib64/qt5/mkspecs/common/sanitize.conf \
		/usr/lib64/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib64/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib64/qt5/mkspecs/common/g++-base.conf \
		/usr/lib64/qt5/mkspecs/common/g++-unix.conf \
		/usr/lib64/qt5/mkspecs/qconfig.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_accessibility_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_core.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_devicediscovery_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_egl_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_eglfsdeviceintegration_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_fb_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_fontdatabase_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_glx_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_gui.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_input_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_kms_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_linuxaccessibility_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_network.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_platformcompositor_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_service_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_sql.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_theme_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_xml.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/usr/lib64/qt5/mkspecs/features/qt_functions.prf \
		/usr/lib64/qt5/mkspecs/features/qt_config.prf \
		/usr/lib64/qt5/mkspecs/linux-g++/qmake.conf \
		/usr/lib64/qt5/mkspecs/features/spec_post.prf \
		.qmake.stash \
		/usr/lib64/qt5/mkspecs/features/exclusive_builds.prf \
		/usr/lib64/qt5/mkspecs/features/toolchain.prf \
		/usr/lib64/qt5/mkspecs/features/default_pre.prf \
		/usr/lib64/qt5/mkspecs/features/resolve_config.prf \
		/usr/lib64/qt5/mkspecs/features/default_post.prf \
		/usr/lib64/qt5/mkspecs/features/qt.prf \
		/usr/lib64/qt5/mkspecs/features/resources.prf \
		/usr/lib64/qt5/mkspecs/features/moc.prf \
		/usr/lib64/qt5/mkspecs/features/unix/opengl.prf \
		/usr/lib64/qt5/mkspecs/features/uic.prf \
		/usr/lib64/qt5/mkspecs/features/unix/thread.prf \
		/usr/lib64/qt5/mkspecs/features/warn_on.prf \
		/usr/lib64/qt5/mkspecs/features/qmake_use.prf \
		/usr/lib64/qt5/mkspecs/features/file_copies.prf \
		/usr/lib64/qt5/mkspecs/features/testcase_targets.prf \
		/usr/lib64/qt5/mkspecs/features/exceptions.prf \
		/usr/lib64/qt5/mkspecs/features/yacc.prf \
		/usr/lib64/qt5/mkspecs/features/lex.prf \
		event_display.pro include/QRootCanvas.h \
		include/QMainCanvas.h \
		include/Viewer.h \
		include/ComponentsSchematic.h \
		include/RootTree.h \
		include/Analyzer.h \
		include/Cluster.h \
		include/ValueType.h \
		include/Config.h \
		include/histos.hpp \
		include/CalibrationConstants.hpp src/main.cpp \
		src/QRootCanvas.cpp \
		src/QMainCanvas.cpp \
		src/Viewer.cpp \
		src/ComponentsSchematic.cpp \
		src/RootTree.cpp \
		src/Analyzer.cpp \
		src/Cluster.cpp \
		src/ValueType.cpp \
		src/Config.cpp
QMAKE_TARGET  = main
DESTDIR       = 
TARGET        = main


first: all
####### Build rules

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: event_display.pro /usr/lib64/qt5/mkspecs/linux-g++/qmake.conf /usr/lib64/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib64/qt5/mkspecs/common/unix.conf \
		/usr/lib64/qt5/mkspecs/common/linux.conf \
		/usr/lib64/qt5/mkspecs/common/sanitize.conf \
		/usr/lib64/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib64/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib64/qt5/mkspecs/common/g++-base.conf \
		/usr/lib64/qt5/mkspecs/common/g++-unix.conf \
		/usr/lib64/qt5/mkspecs/qconfig.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_accessibility_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_core.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_devicediscovery_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_egl_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_eglfsdeviceintegration_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_fb_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_fontdatabase_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_glx_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_gui.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_input_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_kms_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_linuxaccessibility_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_network.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_platformcompositor_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_service_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_sql.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_theme_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_xml.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/usr/lib64/qt5/mkspecs/features/qt_functions.prf \
		/usr/lib64/qt5/mkspecs/features/qt_config.prf \
		/usr/lib64/qt5/mkspecs/linux-g++/qmake.conf \
		/usr/lib64/qt5/mkspecs/features/spec_post.prf \
		.qmake.stash \
		/usr/lib64/qt5/mkspecs/features/exclusive_builds.prf \
		/usr/lib64/qt5/mkspecs/features/toolchain.prf \
		/usr/lib64/qt5/mkspecs/features/default_pre.prf \
		/usr/lib64/qt5/mkspecs/features/resolve_config.prf \
		/usr/lib64/qt5/mkspecs/features/default_post.prf \
		/usr/lib64/qt5/mkspecs/features/qt.prf \
		/usr/lib64/qt5/mkspecs/features/resources.prf \
		/usr/lib64/qt5/mkspecs/features/moc.prf \
		/usr/lib64/qt5/mkspecs/features/unix/opengl.prf \
		/usr/lib64/qt5/mkspecs/features/uic.prf \
		/usr/lib64/qt5/mkspecs/features/unix/thread.prf \
		/usr/lib64/qt5/mkspecs/features/warn_on.prf \
		/usr/lib64/qt5/mkspecs/features/qmake_use.prf \
		/usr/lib64/qt5/mkspecs/features/file_copies.prf \
		/usr/lib64/qt5/mkspecs/features/testcase_targets.prf \
		/usr/lib64/qt5/mkspecs/features/exceptions.prf \
		/usr/lib64/qt5/mkspecs/features/yacc.prf \
		/usr/lib64/qt5/mkspecs/features/lex.prf \
		event_display.pro \
		/usr/lib64/libQt5Widgets.prl \
		/usr/lib64/libQt5Gui.prl \
		/usr/lib64/libQt5Core.prl
	$(QMAKE) -o Makefile event_display.pro
/usr/lib64/qt5/mkspecs/features/spec_pre.prf:
/usr/lib64/qt5/mkspecs/common/unix.conf:
/usr/lib64/qt5/mkspecs/common/linux.conf:
/usr/lib64/qt5/mkspecs/common/sanitize.conf:
/usr/lib64/qt5/mkspecs/common/gcc-base.conf:
/usr/lib64/qt5/mkspecs/common/gcc-base-unix.conf:
/usr/lib64/qt5/mkspecs/common/g++-base.conf:
/usr/lib64/qt5/mkspecs/common/g++-unix.conf:
/usr/lib64/qt5/mkspecs/qconfig.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_accessibility_support_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_concurrent.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_concurrent_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_core.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_core_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_dbus.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_dbus_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_devicediscovery_support_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_egl_support_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_eglfsdeviceintegration_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_fb_support_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_fontdatabase_support_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_glx_support_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_gui.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_gui_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_input_support_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_kms_support_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_linuxaccessibility_support_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_network.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_network_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_opengl.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_opengl_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_openglextensions.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_platformcompositor_support_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_printsupport.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_printsupport_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_service_support_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_sql.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_sql_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_testlib.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_testlib_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_theme_support_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_widgets.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_widgets_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_xml.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_xml_private.pri:
/usr/lib64/qt5/mkspecs/features/qt_functions.prf:
/usr/lib64/qt5/mkspecs/features/qt_config.prf:
/usr/lib64/qt5/mkspecs/linux-g++/qmake.conf:
/usr/lib64/qt5/mkspecs/features/spec_post.prf:
.qmake.stash:
/usr/lib64/qt5/mkspecs/features/exclusive_builds.prf:
/usr/lib64/qt5/mkspecs/features/toolchain.prf:
/usr/lib64/qt5/mkspecs/features/default_pre.prf:
/usr/lib64/qt5/mkspecs/features/resolve_config.prf:
/usr/lib64/qt5/mkspecs/features/default_post.prf:
/usr/lib64/qt5/mkspecs/features/qt.prf:
/usr/lib64/qt5/mkspecs/features/resources.prf:
/usr/lib64/qt5/mkspecs/features/moc.prf:
/usr/lib64/qt5/mkspecs/features/unix/opengl.prf:
/usr/lib64/qt5/mkspecs/features/uic.prf:
/usr/lib64/qt5/mkspecs/features/unix/thread.prf:
/usr/lib64/qt5/mkspecs/features/warn_on.prf:
/usr/lib64/qt5/mkspecs/features/qmake_use.prf:
/usr/lib64/qt5/mkspecs/features/file_copies.prf:
/usr/lib64/qt5/mkspecs/features/testcase_targets.prf:
/usr/lib64/qt5/mkspecs/features/exceptions.prf:
/usr/lib64/qt5/mkspecs/features/yacc.prf:
/usr/lib64/qt5/mkspecs/features/lex.prf:
event_display.pro:
/usr/lib64/libQt5Widgets.prl:
/usr/lib64/libQt5Gui.prl:
/usr/lib64/libQt5Core.prl:
qmake: FORCE
	@$(QMAKE) -o Makefile event_display.pro

qmake_all: FORCE


all: Makefile $(TARGET)

dist: distdir FORCE
	(cd `dirname $(DISTDIR)` && $(TAR) $(DISTNAME).tar $(DISTNAME) && $(COMPRESS) $(DISTNAME).tar) && $(MOVE) `dirname $(DISTDIR)`/$(DISTNAME).tar.gz . && $(DEL_FILE) -r $(DISTDIR)

distdir: FORCE
	@test -d $(DISTDIR) || mkdir -p $(DISTDIR)
	$(COPY_FILE) --parents $(DIST) $(DISTDIR)/
	$(COPY_FILE) --parents /usr/lib64/qt5/mkspecs/features/data/dummy.cpp $(DISTDIR)/
	$(COPY_FILE) --parents include/QRootCanvas.h include/QMainCanvas.h include/Viewer.h include/ComponentsSchematic.h include/RootTree.h include/Analyzer.h include/Cluster.h include/ValueType.h include/Config.h include/histos.hpp include/CalibrationConstants.hpp $(DISTDIR)/
	$(COPY_FILE) --parents src/main.cpp src/QRootCanvas.cpp src/QMainCanvas.cpp src/Viewer.cpp src/ComponentsSchematic.cpp src/RootTree.cpp src/Analyzer.cpp src/Cluster.cpp src/ValueType.cpp src/Config.cpp $(DISTDIR)/


clean: compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


distclean: clean 
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) .qmake.stash
	-$(DEL_FILE) Makefile


####### Sub-libraries

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

check: first

benchmark: first

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_moc_predefs_make_all: moc/moc_predefs.h
compiler_moc_predefs_clean:
	-$(DEL_FILE) moc/moc_predefs.h
moc/moc_predefs.h: /usr/lib64/qt5/mkspecs/features/data/dummy.cpp
	g++ -pipe -O2 -g -pipe -Wall -Wp,-D_FORTIFY_SOURCE=2 -fexceptions -fstack-protector-strong --param=ssp-buffer-size=4 -grecord-gcc-switches -m64 -mtune=generic -O2 -std=gnu++11 -dM -E -o moc/moc_predefs.h /usr/lib64/qt5/mkspecs/features/data/dummy.cpp

compiler_moc_header_make_all: moc/moc_QRootCanvas.cpp moc/moc_QMainCanvas.cpp moc/moc_Viewer.cpp moc/moc_ComponentsSchematic.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc/moc_QRootCanvas.cpp moc/moc_QMainCanvas.cpp moc/moc_Viewer.cpp moc/moc_ComponentsSchematic.cpp
moc/moc_QRootCanvas.cpp: include/QRootCanvas.h \
		moc/moc_predefs.h \
		/usr/lib64/qt5/bin/moc
	/usr/lib64/qt5/bin/moc $(DEFINES) --include moc/moc_predefs.h -I/usr/lib64/qt5/mkspecs/linux-g++ -I/home/vt/event_display_vmm3a -I/home/vt/event_display_vmm3a -I/home/vt/event_display_vmm3a/include -I'/home/vt/event_display_vmm3a/${ROOTSYS}/include' -I/usr/include/qt5 -I/usr/include/qt5/QtWidgets -I/usr/include/qt5/QtGui -I/usr/include/qt5/QtCore -I/usr/include/c++/8 -I/usr/include/c++/8/x86_64-redhat-linux -I/usr/include/c++/8/backward -I/usr/lib/gcc/x86_64-redhat-linux/8/include -I/usr/local/include -I/usr/include include/QRootCanvas.h -o moc/moc_QRootCanvas.cpp

moc/moc_QMainCanvas.cpp: include/QRootCanvas.h \
		include/QMainCanvas.h \
		moc/moc_predefs.h \
		/usr/lib64/qt5/bin/moc
	/usr/lib64/qt5/bin/moc $(DEFINES) --include moc/moc_predefs.h -I/usr/lib64/qt5/mkspecs/linux-g++ -I/home/vt/event_display_vmm3a -I/home/vt/event_display_vmm3a -I/home/vt/event_display_vmm3a/include -I'/home/vt/event_display_vmm3a/${ROOTSYS}/include' -I/usr/include/qt5 -I/usr/include/qt5/QtWidgets -I/usr/include/qt5/QtGui -I/usr/include/qt5/QtCore -I/usr/include/c++/8 -I/usr/include/c++/8/x86_64-redhat-linux -I/usr/include/c++/8/backward -I/usr/lib/gcc/x86_64-redhat-linux/8/include -I/usr/local/include -I/usr/include include/QMainCanvas.h -o moc/moc_QMainCanvas.cpp

moc/moc_Viewer.cpp: include/QMainCanvas.h \
		include/QRootCanvas.h \
		include/ComponentsSchematic.h \
		include/Analyzer.h \
		include/RootTree.h \
		include/histos.hpp \
		include/Viewer.h \
		moc/moc_predefs.h \
		/usr/lib64/qt5/bin/moc
	/usr/lib64/qt5/bin/moc $(DEFINES) --include moc/moc_predefs.h -I/usr/lib64/qt5/mkspecs/linux-g++ -I/home/vt/event_display_vmm3a -I/home/vt/event_display_vmm3a -I/home/vt/event_display_vmm3a/include -I'/home/vt/event_display_vmm3a/${ROOTSYS}/include' -I/usr/include/qt5 -I/usr/include/qt5/QtWidgets -I/usr/include/qt5/QtGui -I/usr/include/qt5/QtCore -I/usr/include/c++/8 -I/usr/include/c++/8/x86_64-redhat-linux -I/usr/include/c++/8/backward -I/usr/lib/gcc/x86_64-redhat-linux/8/include -I/usr/local/include -I/usr/include include/Viewer.h -o moc/moc_Viewer.cpp

moc/moc_ComponentsSchematic.cpp: include/ComponentsSchematic.h \
		moc/moc_predefs.h \
		/usr/lib64/qt5/bin/moc
	/usr/lib64/qt5/bin/moc $(DEFINES) --include moc/moc_predefs.h -I/usr/lib64/qt5/mkspecs/linux-g++ -I/home/vt/event_display_vmm3a -I/home/vt/event_display_vmm3a -I/home/vt/event_display_vmm3a/include -I'/home/vt/event_display_vmm3a/${ROOTSYS}/include' -I/usr/include/qt5 -I/usr/include/qt5/QtWidgets -I/usr/include/qt5/QtGui -I/usr/include/qt5/QtCore -I/usr/include/c++/8 -I/usr/include/c++/8/x86_64-redhat-linux -I/usr/include/c++/8/backward -I/usr/lib/gcc/x86_64-redhat-linux/8/include -I/usr/local/include -I/usr/include include/ComponentsSchematic.h -o moc/moc_ComponentsSchematic.cpp

compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_predefs_clean compiler_moc_header_clean 

####### Compile

obj/main.o: src/main.cpp include/Viewer.h \
		include/QMainCanvas.h \
		include/QRootCanvas.h \
		include/ComponentsSchematic.h \
		include/Analyzer.h \
		include/RootTree.h \
		include/histos.hpp \
		include/Config.h \
		include/ValueType.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/main.o src/main.cpp

obj/QRootCanvas.o: src/QRootCanvas.cpp include/QRootCanvas.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/QRootCanvas.o src/QRootCanvas.cpp

obj/QMainCanvas.o: src/QMainCanvas.cpp include/QMainCanvas.h \
		include/QRootCanvas.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/QMainCanvas.o src/QMainCanvas.cpp

obj/Viewer.o: src/Viewer.cpp include/Viewer.h \
		include/QMainCanvas.h \
		include/QRootCanvas.h \
		include/ComponentsSchematic.h \
		include/Analyzer.h \
		include/RootTree.h \
		include/histos.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Viewer.o src/Viewer.cpp

obj/ComponentsSchematic.o: src/ComponentsSchematic.cpp include/ComponentsSchematic.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/ComponentsSchematic.o src/ComponentsSchematic.cpp

obj/RootTree.o: src/RootTree.cpp include/RootTree.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/RootTree.o src/RootTree.cpp

obj/Analyzer.o: src/Analyzer.cpp include/Analyzer.h \
		include/RootTree.h \
		include/histos.hpp \
		include/Cluster.h \
		include/Config.h \
		include/ValueType.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Analyzer.o src/Analyzer.cpp

obj/Cluster.o: src/Cluster.cpp include/Cluster.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Cluster.o src/Cluster.cpp

obj/ValueType.o: src/ValueType.cpp include/ValueType.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/ValueType.o src/ValueType.cpp

obj/Config.o: src/Config.cpp include/Config.h \
		include/ValueType.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Config.o src/Config.cpp

obj/moc_QRootCanvas.o: moc/moc_QRootCanvas.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_QRootCanvas.o moc/moc_QRootCanvas.cpp

obj/moc_QMainCanvas.o: moc/moc_QMainCanvas.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_QMainCanvas.o moc/moc_QMainCanvas.cpp

obj/moc_Viewer.o: moc/moc_Viewer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_Viewer.o moc/moc_Viewer.cpp

obj/moc_ComponentsSchematic.o: moc/moc_ComponentsSchematic.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_ComponentsSchematic.o moc/moc_ComponentsSchematic.cpp

####### Install

install:  FORCE

uninstall:  FORCE

FORCE:


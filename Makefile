#############################################################################
# Makefile for building: nocturn
# Generated by qmake (2.01a) (Qt 4.8.5) on: pon. lis 11 12:48:20 2013
# Project:  nocturn.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -o Makefile nocturn.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++ -std=c++11
DEFINES       = -DQT_NO_DEBUG -DQT_PHONON_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -march=i686 -mtune=generic -O2 -pipe -fstack-protector --param=ssp-buffer-size=4 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -march=i686 -mtune=generic -O2 -pipe -fstack-protector --param=ssp-buffer-size=4 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/phonon -I/usr/include/qt4 -I. -I/usr/include/qt4/phonon_compat -I. -I.
LINK          = g++
LFLAGS        = -Wl,-O1,--sort-common,--as-needed,-z,relro -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib -lphonon -lQtGui -lQtCore -lpthread -ltag
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = audiomimedata.cpp \
		audiotrackmodel.cpp \
		main.cpp \
		maincontroler.cpp \
		mainview.cpp \
		modelmanager.cpp \
		playbackmanager.cpp \
		playbackmodel.cpp \
		playbackphonon.cpp \
		playlistmanager.cpp \
		playlistmodel.cpp \
		playlistpageview.cpp \
		taghandler.cpp moc_maincontroler.cpp \
		moc_mainview.cpp \
		moc_playbackmanager.cpp \
		moc_playbackmodel.cpp \
		moc_playbackphonon.cpp \
		moc_playlistmodel.cpp \
		moc_playlistpageview.cpp
OBJECTS       = audiomimedata.o \
		audiotrackmodel.o \
		main.o \
		maincontroler.o \
		mainview.o \
		modelmanager.o \
		playbackmanager.o \
		playbackmodel.o \
		playbackphonon.o \
		playlistmanager.o \
		playlistmodel.o \
		playlistpageview.o \
		taghandler.o \
		moc_maincontroler.o \
		moc_mainview.o \
		moc_playbackmanager.o \
		moc_playbackmodel.o \
		moc_playbackphonon.o \
		moc_playlistmodel.o \
		moc_playlistpageview.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		nocturn.pro
QMAKE_TARGET  = nocturn
DESTDIR       = 
TARGET        = nocturn

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_mainform.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: nocturn.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -o Makefile nocturn.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_phonon.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/shared.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile nocturn.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/nocturn1.0.0 || $(MKDIR) .tmp/nocturn1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/nocturn1.0.0/ && $(COPY_FILE) --parents audiomimedata.h audiotrackmodel.h maincontroler.h mainview.h modelmanager.h playbackmanager.h playbackmodel.h playbackphonon.h playlistmanager.h playlistmodel.h playlistpageview.h taghandler.h .tmp/nocturn1.0.0/ && $(COPY_FILE) --parents audiomimedata.cpp audiotrackmodel.cpp main.cpp maincontroler.cpp mainview.cpp modelmanager.cpp playbackmanager.cpp playbackmodel.cpp playbackphonon.cpp playlistmanager.cpp playlistmodel.cpp playlistpageview.cpp taghandler.cpp .tmp/nocturn1.0.0/ && $(COPY_FILE) --parents mainform.ui .tmp/nocturn1.0.0/ && (cd `dirname .tmp/nocturn1.0.0` && $(TAR) nocturn1.0.0.tar nocturn1.0.0 && $(COMPRESS) nocturn1.0.0.tar) && $(MOVE) `dirname .tmp/nocturn1.0.0`/nocturn1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/nocturn1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_maincontroler.cpp moc_mainview.cpp moc_playbackmanager.cpp moc_playbackmodel.cpp moc_playbackphonon.cpp moc_playlistmodel.cpp moc_playlistpageview.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_maincontroler.cpp moc_mainview.cpp moc_playbackmanager.cpp moc_playbackmodel.cpp moc_playbackphonon.cpp moc_playlistmodel.cpp moc_playlistpageview.cpp
moc_maincontroler.cpp: maincontroler.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) maincontroler.h -o moc_maincontroler.cpp

moc_mainview.cpp: ui_mainform.h \
		mainview.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) mainview.h -o moc_mainview.cpp

moc_playbackmanager.cpp: playbackmodel.h \
		playbackphonon.h \
		playbackmanager.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) playbackmanager.h -o moc_playbackmanager.cpp

moc_playbackmodel.cpp: playbackmodel.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) playbackmodel.h -o moc_playbackmodel.cpp

moc_playbackphonon.cpp: playbackmodel.h \
		playbackphonon.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) playbackphonon.h -o moc_playbackphonon.cpp

moc_playlistmodel.cpp: playlistmodel.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) playlistmodel.h -o moc_playlistmodel.cpp

moc_playlistpageview.cpp: playlistpageview.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) playlistpageview.h -o moc_playlistpageview.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainform.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainform.h
ui_mainform.h: mainform.ui
	/usr/lib/qt4/bin/uic mainform.ui -o ui_mainform.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

audiomimedata.o: audiomimedata.cpp audiomimedata.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o audiomimedata.o audiomimedata.cpp

audiotrackmodel.o: audiotrackmodel.cpp audiotrackmodel.h \
		taghandler.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o audiotrackmodel.o audiotrackmodel.cpp

main.o: main.cpp mainview.h \
		ui_mainform.h \
		maincontroler.h \
		modelmanager.h \
		playbackmodel.h \
		playlistmanager.h \
		playbackmanager.h \
		playbackphonon.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

maincontroler.o: maincontroler.cpp maincontroler.h \
		modelmanager.h \
		playbackmodel.h \
		playlistmanager.h \
		playbackmanager.h \
		playbackphonon.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o maincontroler.o maincontroler.cpp

mainview.o: mainview.cpp mainview.h \
		ui_mainform.h \
		maincontroler.h \
		playlistpageview.h \
		playbackmodel.h \
		playbackphonon.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainview.o mainview.cpp

modelmanager.o: modelmanager.cpp modelmanager.h \
		playbackmodel.h \
		playlistmanager.h \
		playbackmanager.h \
		playbackphonon.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o modelmanager.o modelmanager.cpp

playbackmanager.o: playbackmanager.cpp playbackmanager.h \
		playbackmodel.h \
		playbackphonon.h \
		maincontroler.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o playbackmanager.o playbackmanager.cpp

playbackmodel.o: playbackmodel.cpp playbackmodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o playbackmodel.o playbackmodel.cpp

playbackphonon.o: playbackphonon.cpp playbackphonon.h \
		playbackmodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o playbackphonon.o playbackphonon.cpp

playlistmanager.o: playlistmanager.cpp playlistmanager.h \
		playlistmodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o playlistmanager.o playlistmanager.cpp

playlistmodel.o: playlistmodel.cpp playlistmodel.h \
		maincontroler.h \
		audiotrackmodel.h \
		taghandler.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o playlistmodel.o playlistmodel.cpp

playlistpageview.o: playlistpageview.cpp playlistpageview.h \
		playlistmodel.h \
		maincontroler.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o playlistpageview.o playlistpageview.cpp

taghandler.o: taghandler.cpp taghandler.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o taghandler.o taghandler.cpp

moc_maincontroler.o: moc_maincontroler.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_maincontroler.o moc_maincontroler.cpp

moc_mainview.o: moc_mainview.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainview.o moc_mainview.cpp

moc_playbackmanager.o: moc_playbackmanager.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_playbackmanager.o moc_playbackmanager.cpp

moc_playbackmodel.o: moc_playbackmodel.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_playbackmodel.o moc_playbackmodel.cpp

moc_playbackphonon.o: moc_playbackphonon.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_playbackphonon.o moc_playbackphonon.cpp

moc_playlistmodel.o: moc_playlistmodel.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_playlistmodel.o moc_playlistmodel.cpp

moc_playlistpageview.o: moc_playlistpageview.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_playlistpageview.o moc_playlistpageview.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:


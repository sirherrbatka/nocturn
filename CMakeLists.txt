project(nocturn)
set(CMAKE_AUTOMOC ON)

cmake_minimum_required(VERSION 2.8)

ADD_DEFINITIONS(
    -std=c++11 # Or -std=c++0x
    # Other flags
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

FIND_PACKAGE(Qt4 REQUIRED QtCore QtGui)
FIND_PACKAGE(TAGLIB REQUIRED)
FIND_PACKAGE(Phonon REQUIRED)
INCLUDE(${QT_USE_FILE} ${TAGLIB_INCLUDE_DIRS})
include_directories(${PHONON_INCLUDES})
include_directories(${TAGLIB_INCLUDES})
ADD_DEFINITIONS(${QT_DEFINITIONS})

SET(nocturn_SOURCES playlistmodelfilehandler.cpp keyhandler.cpp mainviewkeyhandler.cpp audiotrackmodel.cpp maincontroler.cpp mainview.cpp modelmanager.cpp nocturn.cpp playbackmanager.cpp playbackmodel.cpp playbackphonon.cpp playlistmanager.cpp playlistmodel.cpp playlistpageview.cpp playlistpageviewitem.cpp taghandler.cpp main.cpp)

set(nocturn_HEADERS audiotrackmodel.h maincontroler.h mainview.h modelmanager.h nocturn.h playbackmanager.h playbackmodel.h playbackphonon.h playlistmanager.h playlistmodel.h playlistpageview.h playlistpageviewitem.h sharedtypes.h taghandler.h)
SET(nocturn_FORMS mainform.ui)
set(QT_USE_PHONON TRUE)
set(QTCORELIBS ${QT_QTCORE_LIBRARY})
set(QTGUILIBS ${QT_QTGUI_LIBRARY})
QT4_WRAP_UI(nocturn_FORMS_HEADERS ${nocturn_FORMS})
QT4_WRAP_CPP(nocturn_HEADERS_MOC )
ADD_EXECUTABLE(nocturn ${nocturn_SOURCES} ${nocturn_FORMS_HEADERS} ${nocturn_HEADERS_MOC})
set(CMAKE_CXX_FLAGS"-Wall -ggdb -Wextra -Weffc++ -Werror -Wshadow -pedantic -Wsign-compare -Wmaybe-uninitialized")
  
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
TARGET_LINK_LIBRARIES(nocturn 
${QT_LIBRARIES}
${TAGLIB_LIBRARIES}
${PHONON_LIBS}
)

install(TARGETS nocturn RUNTIME DESTINATION bin)
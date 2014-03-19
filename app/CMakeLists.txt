set (NOCTURN_SRC main.cpp)

FIND_PACKAGE(Qt4 REQUIRED QtCore QtGui)
FIND_PACKAGE(TAGLIB REQUIRED)
FIND_PACKAGE(Phonon REQUIRED)
INCLUDE(${QT_USE_FILE} ${TAGLIB_INCLUDE_DIRS})
include_directories(${PHONON_INCLUDES})
include_directories(${TAGLIB_INCLUDES})
ADD_DEFINITIONS(${QT_DEFINITIONS})

SET(nocturn_FORMS mainform.ui configform.ui newstreamform.ui)
SET(nocturn_SOURCES streamsmenuwrapper.cpp audiotrackproxy.cpp systrayiconwrapper.cpp settingsview.cpp settingsmanager.cpp playlistmodelfilehandler.cpp keyhandler.cpp mainviewkeyhandler.cpp audiotrackmodel.cpp maincontroler.cpp mainview.cpp modelmanager.cpp nocturn.cpp playbackmanager.cpp playbackmodel.cpp playbackphonon.cpp playlistmanager.cpp playlistmodel.cpp playlistpageview.cpp playlistpageviewitem.cpp taghandler.cpp main.cpp)
SET(nocturn_RESOURCES resources.qrc)

QT4_ADD_RESOURCES(nocturn_RESOURCES_RCC ${nocturn_RESOURCES})
QT4_WRAP_UI(nocturn_FORMS_HEADERS ${nocturn_FORMS})
QT4_WRAP_CPP(moc_SRCS ${nocturn_MOC_FILES})

set(nocturn_HEADERS audiotrackmodel.h maincontroler.h mainview.h modelmanager.h nocturn.h playbackmanager.h playbackmodel.h playbackphonon.h playlistmanager.h playlistmodel.h playlistpageview.h playlistpageviewitem.h sharedtypes.h taghandler.h)
set(QT_USE_PHONON TRUE)
set(QTCORELIBS ${QT_QTCORE_LIBRARY})
set(QTGUILIBS ${QT_QTGUI_LIBRARY})
ADD_EXECUTABLE(nocturn ${nocturn_SOURCES} ${nocturn_FORMS_HEADERS} ${nocturn_HEADERS_MOC} ${nocturn_RESOURCES_RCC})
set(CMAKE_CXX_FLAGS"-Wall -ggdb -Wextra -Weffc++ -Werror -Wshadow -pedantic -Wsign-compare -Wmaybe-uninitialized")

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

add_library(player STATIC ${nocturn_SOURCES} ${nocturn_HEADERS_MOC})

TARGET_LINK_LIBRARIES(nocturn
${QT_LIBRARIES}
${TAGLIB_LIBRARIES}
${PHONON_LIBS}
)
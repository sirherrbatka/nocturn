# TODO: This should not be needed, check how it was done in FindGTEST
project(TESTS)
set(GMOCK_ROOT "/usr/include")
set(GMOCK_BUILD "/usr/lib")

FIND_PACKAGE(Qt4 REQUIRED QtCore QtGui)
FIND_PACKAGE(TAGLIB REQUIRED)
FIND_PACKAGE(Phonon REQUIRED)
INCLUDE(${QT_USE_FILE} ${TAGLIB_INCLUDE_DIRS})
include_directories(${PHONON_INCLUDES})
include_directories(${TAGLIB_INCLUDES})
find_package(GTest REQUIRED)
find_package(GMock REQUIRED)

if (GTEST_FOUND AND GMOCK_FOUND)

    include_directories(${GTEST_INCLUDE_DIRS})
    include_directories(${GMOCK_INCLUDE_DIRS})

    file(GLOB UNITTEST_SRC_FILES
	components/test_*.cpp
    )

    source_group(tests FILES tests.cpp ${UNITTEST_SRC_FILES})

    add_executable(tests tests.cpp ${UNITTEST_SRC_FILES})

    target_link_libraries(tests ${GMOCK_BOTH_LIBRARIES} ${GTEST_BOTH_LIBRARIES} ${QT_LIBRARIES} ${TAGLIB_LIBRARIES} ${PHONON_LIBS} player)
    # Fix for not visible pthreads functions for linker with glibc 2.15
endif()

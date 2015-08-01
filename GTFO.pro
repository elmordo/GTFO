#-------------------------------------------------
#
# Project created by QtCreator 2015-07-31T23:16:19
#
#-------------------------------------------------

QT       -= core gui

TARGET = GTFO
TEMPLATE = lib

DEFINES += GTFO_LIBRARY

SOURCES +=

HEADERS += \
    src/GTFO/AssertException.hpp \
    src/GTFO/AssertReport.hpp \
    src/GTFO/asserts.hpp \
    src/GTFO/Profiler.hpp \
    src/GTFO/TestBase.hpp \
    src/GTFO/TestCase.hpp \
    src/GTFO/TestCaseReport.hpp \
    src/GTFO/TestGroup.hpp \
    src/GTFO/TestGroupSettings.hpp \
    src/GTFO/TestSuite.hpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}

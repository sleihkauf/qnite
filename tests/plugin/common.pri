TEMPLATE = app
QT += testlib
CONFIG += testcase
LIBS += -L$$OUT_PWD/../../../modules/Qnite/ -lqnite
DESTDIR = ../bin
QMAKE_RPATHDIR += $$OUT_PWD/../bin/

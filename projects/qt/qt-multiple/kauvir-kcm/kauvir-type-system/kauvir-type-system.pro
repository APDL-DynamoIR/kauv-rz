
#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = kauvir-type-system

include(../build-group.pri)


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR


CONFIG += no_keywords

ECL_DIR = /extension/ecl
CL_CXX_DIR = /extension/ecl/cl-cxx
INCLUDEPATH += $$ECL_DIR/install/include
INCLUDEPATH += $$CL_CXX_DIR/install/include/cl-cxx
INCLUDEPATH += $$CL_CXX_DIR/install/include


message($$SRC_DIR)

DEFINES += USE_KANS



HEADERS += \
  $$SRC_DIR/kauvir-type-system.h \
  $$SRC_DIR/kauvir-type-object.h \
  $$SRC_DIR/kauvir-type-attribution-context.h \
  $$SRC_DIR/kauvir-universal-class.h \




SOURCES += \
  $$SRC_DIR/kauvir-type-system.cpp \
  $$SRC_DIR/kauvir-type-attribution-context.cpp \
  $$SRC_DIR/kauvir-type-object.cpp \
  $$SRC_DIR/kauvir-universal-class.cpp \



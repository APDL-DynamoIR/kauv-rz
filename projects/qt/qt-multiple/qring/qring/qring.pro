
#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = qring

include(../build-group.pri)


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$KAUVIR_KCM_SRC_GROUP_DIR


CONFIG += no_keywords


DEFINES += USE_KANS


INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR \
  $$KAUVIR_KCM_SRC_GROUP_DIR/kauvir-type-system \
  $$KAUVIR_KCM_SRC_GROUP_DIR/kauvir-code-model


HEADERS += \
  $$SRC_DIR/qring.h \
  $$SRC_DIR/qring-file-structure.h \

SOURCES += \
  $$SRC_DIR/qring.cpp \
  $$SRC_DIR/qring-file-structure.cpp \

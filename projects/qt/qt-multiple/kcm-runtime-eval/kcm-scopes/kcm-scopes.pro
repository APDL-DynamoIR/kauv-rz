
#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = kcm-scopes

include(../build-group.pri)



INCLUDEPATH += $$KAUVIR_SRC_GROUP_DIR \
  $$KAUVIR_SRC_GROUP_DIR/kauvir-type-system

HEADERS +=  \
  $$SRC_DIR/kcm-scope-system.h \
  $$SRC_DIR/kcm-runtime-scope.h \
  $$SRC_DIR/kcm-lexical-scope.h \


SOURCES +=  \
  $$SRC_DIR/kcm-scope-system.cpp \
  $$SRC_DIR/kcm-runtime-scope.cpp \
  $$SRC_DIR/kcm-lexical-scope.cpp \

CONFIG += no_keywords


LIBS += -L$$TARGETSDIR

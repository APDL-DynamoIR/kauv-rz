
#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = basic-functions


include(../build-group.pri)

include(../../find-ecl-sexp.pri)


INCLUDEPATH += $$KAUVIR_SRC_GROUP_DIR \
  $$KAUVIR_SRC_GROUP_DIR/kauvir-type-system

HEADERS +=  \
  $$SRC_DIR/rz-dynamo-basic-functions.h \

SOURCES +=  \
  $$SRC_DIR/rz-dynamo-basic-functions.cpp \

CONFIG += no_keywords


LIBS += -L$$TARGETSDIR -lkauvir-code-model -lkcm-command-runtime -lkcm-lisp-bridge

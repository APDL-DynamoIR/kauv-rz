
#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = kcm-command-runtime

QT += widgets

include(../build-group.pri)

INCLUDEPATH += $$SRC_GROUP_DIR

INCLUDEPATH += $$KAUVIR_SRC_GROUP_DIR



include(../../find-ecl-sexp.pri)


HEADERS +=  \
  $$SRC_DIR/kcm-command-runtime-router.h \
  $$SRC_DIR/kcm-command-runtime-router-qob.h \
  $$SRC_DIR/kcm-command-runtime-argument.h \
  $$SRC_DIR/kcm-command-runtime-table.h \
  $$SRC_DIR/kcm-command-runtime-router-cast-schedule.h \


SOURCES +=  \
  $$SRC_DIR/kcm-command-runtime-router.cpp \
  $$SRC_DIR/kcm-command-runtime-argument.cpp \
  $$SRC_DIR/kcm-command-runtime-table.cpp \



CONFIG += no_keywords


LIBS += -L$$TARGETSDIR -lkcm-scopes -lkauvir-code-model \
  -lkcm-command-package -lkcm-lisp-bridge

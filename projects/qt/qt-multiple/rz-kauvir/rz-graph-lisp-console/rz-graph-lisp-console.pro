
#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

QT += widgets network


PROJECT_NAME = rz-graph-lisp-console

include(../build-group.pri)

TEMPLATE = app
CONFIG += console

DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR \
  $$SRC_GROUP_DIR/rz-graph-core  $$SRC_GROUP_DIR/rz-graph-token  \
  $$RELAE_SRC_GROUP_DIR  $$KAUVIR_KCM_SRC_GROUP_DIR


CONFIG += no_keywords


include(../../find-ecl-sexp.pri)


INCLUDEPATH += $$SEXP_DIR
INCLUDEPATH += $$SEXP_DIR/pingus/


SOURCES += \
  $$SRC_DIR/main.cpp

LIBS += -L$$TARGETSDIR  \
   -lrz-graph-core \
   -lrz-graph-token \
   -lrz-graph-code \
   -lrz-graph-visit \
   -lrz-code-generators \
   -lrz-graph-build \
   -lrz-graph-valuer \
   -lrz-graph-embed \
   -lrz-graph-embed-run \
   -lrz-graph-run \
   -lrz-graph-sre \
   -lrz-function-def \
   -lrz-code-elements \


LIBS += -lrz-code-generators

LIBS += -L$$TARGETSDIR -lsexpr

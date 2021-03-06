
#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = rz-dynamo-console

include(../build-group.pri)

TEMPLATE = app

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR
INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR $$KAUVIR_KCM_SRC_GROUP_DIR/kcm-lisp-bridge


message($$KAUVIR_KCM_SRC_GROUP_DIR)

CONFIG += no_keywords

DEFINES += USE_KANS

include(../../find-ecl-sexp.pri)

SOURCES += \
  $$SRC_DIR/main.cpp \



LIBS += -L$$TARGETSDIR -lkcm-lisp-bridge  \
  -lkauvir-code-model -lkauvir-type-system -lrz-dynamo-generator

LIBS += -L$$TARGETSDIR -lkcm-command-package -lkcm-command-runtime \
   -lkcm-direct-eval -lPhaonLib


LIBS += -L$$ECL_DIR -lecl
LIBS += -L$$CL_CXX_DIR/install/lib64 -lcl_cxx

LIBS += -L$$TARGETSDIR -lsexpr -lkcm-scopes

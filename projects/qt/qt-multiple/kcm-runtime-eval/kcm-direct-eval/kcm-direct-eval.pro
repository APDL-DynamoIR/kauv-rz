
#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = kcm-direct-eval

include(../build-group.pri)



INCLUDEPATH += $$KAUVIR_SRC_GROUP_DIR \
  $$KAUVIR_SRC_GROUP_DIR/kauvir-type-system



HEADERS +=  \
  $$SRC_DIR/kcm-direct-eval.h \


LIBS += -L$$TARGETSDIR -lkcm-command-package  -lkcm-scopes \
  -lkcm-command-runtime -lkauvir-code-model -lkcm-lisp-bridge \


SOURCES +=  \
  $$SRC_DIR/kcm-direct-eval.cpp \


CONFIG += no_keywords


LIBS += -L$$TARGETSDIR

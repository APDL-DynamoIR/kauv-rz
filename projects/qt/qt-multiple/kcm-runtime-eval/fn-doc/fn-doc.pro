
#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


PROJECT_NAME = fn-doc


include(../build-group.pri)



INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR \
  $$KAUVIR_KCM_SRC_GROUP_DIR/kauvir-type-system \
  $$KAUVIR_KCM_SRC_GROUP_DIR/kauvir-code-model



HEADERS +=  \
  $$SRC_DIR/fn-doc.h \


SOURCES +=  \
  $$SRC_DIR/fn-doc.cpp \

CONFIG += no_keywords


LIBS += -L$$TARGETSDIR -lkcm-scopes -lkcm-env -lkcm-env


#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = rz-graph-embed-run

#depends on: rz-graph-valuer

include(../build-group.pri)

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR  $$SRC_GROUP_DIR/rz-graph-core  \
  $$SRC_GROUP_DIR/rz-graph-token \
  $$RELAE_SRC_GROUP_DIR


DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES


LIBS += -L$$TARGETSDIR -lrz-graph-valuer


HEADERS += \
   $$SRC_DIR/rz-graph-embed-run-valuer.h \


SOURCES += \
   $$SRC_DIR/rz-graph-embed-run-valuer.cpp \


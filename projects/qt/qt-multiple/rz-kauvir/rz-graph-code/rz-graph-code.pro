
#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = rz-graph-code

include(../build-group.pri)

#depends on  rz-graph-visit  rz-graph-sre  rz-graph-core  rz-graph-token  rz-graph-run
#  rz-graph-valuer  rz-clasp-project  rz-code-generators

INCLUDEPATH += $$SRC_DIR $$SRC_ROOT_DIR $$SRC_GROUP_DIR  \
  $$SRC_GROUP_DIR/rz-graph-token  $$SRC_GROUP_DIR/rz-graph-core \
  $$RELAE_SRC_GROUP_DIR


INCLUDEPATH += $$MSME_RELAE_CORE_GROUP_DIR


LIBS += -L$$TARGETSDIR -lrz-graph-visit -lrz-graph-sre -lrz-code-generators    \
 -lrz-graph-core -lrz-graph-token -lrz-graph-run -lrz-graph-valuer  \
 -lrz-code-generators  -lrz-function-def

DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES


DEFINES += RELAE_LABEL_NODES
DEFINES += CAON_DEBUG


HEADERS += \
  $$SRC_DIR/prerun/rz-re-prerun-anticipate.h \
  $$SRC_DIR/prerun/rz-re-prerun-normalize.h \
  $$SRC_DIR/prerun/rz-re-prerun-tokens.h \


SOURCES += \
  $$SRC_DIR/prerun/rz-re-prerun-anticipate.cpp \
  $$SRC_DIR/prerun/rz-re-prerun-normalize.cpp \
  $$SRC_DIR/prerun/rz-re-prerun-tokens.cpp \





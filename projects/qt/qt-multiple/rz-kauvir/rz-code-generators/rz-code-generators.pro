
#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = rz-code-generators

include(../build-group.pri)

#depends on: rz-graph-visit  rz-code-elements

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR \
  $$SRC_GROUP_DIR/rz-graph-token \
  $$SRC_GROUP_DIR/rz-graph-core \
  $$RELAE_SRC_GROUP_DIR


DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES
DEFINES += RZ_CPP_GEN


TEMPLATE = lib



HEADERS += \
  $$SRC_ROOT_DIR/multistep-token.h \
  $$SRC_DIR/rz-dynamo-output.h \
  $$SRC_DIR/rz-dynamo-block.h \
  $$SRC_DIR/rz-dynamo-form.h \
  $$SRC_DIR/rz-dynamo-form-annotation.h \
  $$SRC_DIR/rz-dynamo-expression.h \
  $$SRC_DIR/rz-dynamo-type-declaration.h \


SOURCES += \
  $$SRC_DIR/rz-dynamo-output.cpp \
  $$SRC_DIR/rz-dynamo-block.cpp \
  $$SRC_DIR/rz-dynamo-form.cpp \
  $$SRC_DIR/rz-dynamo-form-annotation.cpp \
  $$SRC_DIR/rz-dynamo-expression.cpp \
  $$SRC_DIR/rz-dynamo-type-declaration.cpp \


LIBS += -L$$TARGETSDIR -lrz-graph-core -lrz-graph-token -lrz-graph-visit \
  -lrz-graph-valuer -lrz-function-def -lrz-code-elements


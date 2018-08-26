
#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = dygred-sentence

include(../build-group.pri)


INCLUDEPATH += $$SRC_GROUP_DIR/udpipe


HEADERS += \
    $$SRC_DIR/dygred-sentence.h \
    $$SRC_DIR/dygred-corpus.h \


SOURCES += \
    $$SRC_DIR/dygred-sentence.cpp \
    $$SRC_DIR/dygred-corpus.cpp \


LIBS += -L$$TARGETSDIR -ludpipe -lqring


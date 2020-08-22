######################################################################
# Automatically generated by qmake (3.1) Fri Aug 21 16:27:36 2020
######################################################################

TEMPLATE = app
TARGET = Sequencer
INCLUDEPATH += .
QT += core gui widgets

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += CImg.h \
           Diagram.h \
           DiagramParser.h \
           Interaction.h \
           InteractionParser.h \
           LayoutConstants.h \
           MetaData.h \
           MetaDataParser.h \
           Participant.h \
           ParticipantsParser.h \
           RenderableDiagram.h \
           RenderableInteraction.h \
           RenderableMetaData.h \
           RenderableParticipant.h \
           RenderingJob.h \
           RenderingThread.h \
           RenderingUtils.h \
           Sequencer.h \
           stdafx.h \
           StringUtils.h
FORMS += Sequencer.ui
SOURCES += Diagram.cpp \
           DiagramParser.cpp \
           Interaction.cpp \
           InteractionParser.cpp \
           main.cpp \
           MetaData.cpp \
           MetaDataParser.cpp \
           Participant.cpp \
           ParticipantsParser.cpp \
           RenderableDiagram.cpp \
           RenderableInteraction.cpp \
           RenderableMetaData.cpp \
           RenderableParticipant.cpp \
           RenderingJob.cpp \
           RenderingThread.cpp \
           RenderingUtils.cpp \
           Sequencer.cpp \
           stdafx.cpp

RESOURCES += Sequencer.qrc

QMAKE_CXXFLAGS += /std:c++17
QMAKE_CXXFLAGS_DEBUG += /MTd
QMAKE_CXXFLAGS_RELEASE += /MT

CONFIG += static
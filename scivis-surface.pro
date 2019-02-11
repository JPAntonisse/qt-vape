QT += quick \
    datavisualization \
    gui \
    widgets
CONFIG += c++11


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# include libararies
INCLUDEPATH += fftw-2.1.3/fftw \
                fftw-2.1.3/rfftw

LIBS += -L library/FFTW.lib

SOURCES += main.cpp \
    surfacegraph.cpp \
    inputhandler.cpp \
    simulation.cpp \
    fftw-2.1.3/fftw/config.c \
    fftw-2.1.3/fftw/executor.c \
    fftw-2.1.3/fftw/fftwf77.c \
    fftw-2.1.3/fftw/fftwnd.c \
    fftw-2.1.3/fftw/fn_1.c \
    fftw-2.1.3/fftw/fn_10.c \
    fftw-2.1.3/fftw/fn_11.c \
    fftw-2.1.3/fftw/fn_12.c \
    fftw-2.1.3/fftw/fn_13.c \
    fftw-2.1.3/fftw/fn_14.c \
    fftw-2.1.3/fftw/fn_15.c \
    fftw-2.1.3/fftw/fn_16.c \
    fftw-2.1.3/fftw/fn_2.c \
    fftw-2.1.3/fftw/fn_3.c \
    fftw-2.1.3/fftw/fn_32.c \
    fftw-2.1.3/fftw/fn_4.c \
    fftw-2.1.3/fftw/fn_5.c \
    fftw-2.1.3/fftw/fn_6.c \
    fftw-2.1.3/fftw/fn_64.c \
    fftw-2.1.3/fftw/fn_7.c \
    fftw-2.1.3/fftw/fn_8.c \
    fftw-2.1.3/fftw/fn_9.c \
    fftw-2.1.3/fftw/fni_1.c \
    fftw-2.1.3/fftw/fni_10.c \
    fftw-2.1.3/fftw/fni_11.c \
    fftw-2.1.3/fftw/fni_12.c \
    fftw-2.1.3/fftw/fni_13.c \
    fftw-2.1.3/fftw/fni_14.c \
    fftw-2.1.3/fftw/fni_15.c \
    fftw-2.1.3/fftw/fni_16.c \
    fftw-2.1.3/fftw/fni_2.c \
    fftw-2.1.3/fftw/fni_3.c \
    fftw-2.1.3/fftw/fni_32.c \
    fftw-2.1.3/fftw/fni_4.c \
    fftw-2.1.3/fftw/fni_5.c \
    fftw-2.1.3/fftw/fni_6.c \
    fftw-2.1.3/fftw/fni_64.c \
    fftw-2.1.3/fftw/fni_7.c \
    fftw-2.1.3/fftw/fni_8.c \
    fftw-2.1.3/fftw/fni_9.c \
    fftw-2.1.3/fftw/ftw_10.c \
    fftw-2.1.3/fftw/ftw_16.c \
    fftw-2.1.3/fftw/ftw_2.c \
    fftw-2.1.3/fftw/ftw_3.c \
    fftw-2.1.3/fftw/ftw_32.c \
    fftw-2.1.3/fftw/ftw_4.c \
    fftw-2.1.3/fftw/ftw_5.c \
    fftw-2.1.3/fftw/ftw_6.c \
    fftw-2.1.3/fftw/ftw_64.c \
    fftw-2.1.3/fftw/ftw_7.c \
    fftw-2.1.3/fftw/ftw_8.c \
    fftw-2.1.3/fftw/ftw_9.c \
    fftw-2.1.3/fftw/ftwi_10.c \
    fftw-2.1.3/fftw/ftwi_16.c \
    fftw-2.1.3/fftw/ftwi_2.c \
    fftw-2.1.3/fftw/ftwi_3.c \
    fftw-2.1.3/fftw/ftwi_32.c \
    fftw-2.1.3/fftw/ftwi_4.c \
    fftw-2.1.3/fftw/ftwi_5.c \
    fftw-2.1.3/fftw/ftwi_6.c \
    fftw-2.1.3/fftw/ftwi_64.c \
    fftw-2.1.3/fftw/ftwi_7.c \
    fftw-2.1.3/fftw/ftwi_8.c \
    fftw-2.1.3/fftw/ftwi_9.c \
    fftw-2.1.3/fftw/generic.c \
    fftw-2.1.3/fftw/malloc.c \
    fftw-2.1.3/fftw/planner.c \
    fftw-2.1.3/fftw/putils.c \
    fftw-2.1.3/fftw/rader.c \
    fftw-2.1.3/fftw/timer.c \
    fftw-2.1.3/fftw/twiddle.c \
    fftw-2.1.3/fftw/wisdom.c \
    fftw-2.1.3/fftw/wisdomio.c \
    fftw-2.1.3/rfftw/fcr_1.c \
    fftw-2.1.3/rfftw/fcr_10.c \
    fftw-2.1.3/rfftw/fcr_11.c \
    fftw-2.1.3/rfftw/fcr_12.c \
    fftw-2.1.3/rfftw/fcr_128.c \
    fftw-2.1.3/rfftw/fcr_13.c \
    fftw-2.1.3/rfftw/fcr_14.c \
    fftw-2.1.3/rfftw/fcr_15.c \
    fftw-2.1.3/rfftw/fcr_16.c \
    fftw-2.1.3/rfftw/fcr_2.c \
    fftw-2.1.3/rfftw/fcr_3.c \
    fftw-2.1.3/rfftw/fcr_32.c \
    fftw-2.1.3/rfftw/fcr_4.c \
    fftw-2.1.3/rfftw/fcr_5.c \
    fftw-2.1.3/rfftw/fcr_6.c \
    fftw-2.1.3/rfftw/fcr_64.c \
    fftw-2.1.3/rfftw/fcr_7.c \
    fftw-2.1.3/rfftw/fcr_8.c \
    fftw-2.1.3/rfftw/fcr_9.c \
    fftw-2.1.3/rfftw/fhb_10.c \
    fftw-2.1.3/rfftw/fhb_16.c \
    fftw-2.1.3/rfftw/fhb_2.c \
    fftw-2.1.3/rfftw/fhb_3.c \
    fftw-2.1.3/rfftw/fhb_32.c \
    fftw-2.1.3/rfftw/fhb_4.c \
    fftw-2.1.3/rfftw/fhb_5.c \
    fftw-2.1.3/rfftw/fhb_6.c \
    fftw-2.1.3/rfftw/fhb_7.c \
    fftw-2.1.3/rfftw/fhb_8.c \
    fftw-2.1.3/rfftw/fhb_9.c \
    fftw-2.1.3/rfftw/fhf_10.c \
    fftw-2.1.3/rfftw/fhf_16.c \
    fftw-2.1.3/rfftw/fhf_2.c \
    fftw-2.1.3/rfftw/fhf_3.c \
    fftw-2.1.3/rfftw/fhf_32.c \
    fftw-2.1.3/rfftw/fhf_4.c \
    fftw-2.1.3/rfftw/fhf_5.c \
    fftw-2.1.3/rfftw/fhf_6.c \
    fftw-2.1.3/rfftw/fhf_7.c \
    fftw-2.1.3/rfftw/fhf_8.c \
    fftw-2.1.3/rfftw/fhf_9.c \
    fftw-2.1.3/rfftw/frc_1.c \
    fftw-2.1.3/rfftw/frc_10.c \
    fftw-2.1.3/rfftw/frc_11.c \
    fftw-2.1.3/rfftw/frc_12.c \
    fftw-2.1.3/rfftw/frc_128.c \
    fftw-2.1.3/rfftw/frc_13.c \
    fftw-2.1.3/rfftw/frc_14.c \
    fftw-2.1.3/rfftw/frc_15.c \
    fftw-2.1.3/rfftw/frc_16.c \
    fftw-2.1.3/rfftw/frc_2.c \
    fftw-2.1.3/rfftw/frc_3.c \
    fftw-2.1.3/rfftw/frc_32.c \
    fftw-2.1.3/rfftw/frc_4.c \
    fftw-2.1.3/rfftw/frc_5.c \
    fftw-2.1.3/rfftw/frc_6.c \
    fftw-2.1.3/rfftw/frc_64.c \
    fftw-2.1.3/rfftw/frc_7.c \
    fftw-2.1.3/rfftw/frc_8.c \
    fftw-2.1.3/rfftw/frc_9.c \
    fftw-2.1.3/rfftw/rconfig.c \
    fftw-2.1.3/rfftw/rexec.c \
    fftw-2.1.3/rfftw/rexec2.c \
    fftw-2.1.3/rfftw/rfftwf77.c \
    fftw-2.1.3/rfftw/rfftwnd.c \
    fftw-2.1.3/rfftw/rgeneric.c \
    fftw-2.1.3/rfftw/rplanner.c



HEADERS += surfacegraph.h \
    inputhandler.h \
    simulation.h \
    fftw-2.1.3/fftw/config.h \
    fftw-2.1.3/fftw/config.h.in \
    fftw-2.1.3/fftw/f77_func.h \
    fftw-2.1.3/fftw/fftw-int.h \
    fftw-2.1.3/fftw/fftw.h \
    fftw-2.1.3/fftw/fftw.h.in \
    fftw-2.1.3/rfftw/rfftw.h \
    inputhandler.h \
    simulation.h \
    surfacegraph.h

QT += quick \
    datavisualization \
    gui \
    widgets

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


DISTFILES += \
    fftw-2.1.3/fftw/stamp-h1.in \
    fftw-2.1.3/fftw/stamp-h2.in

RESOURCES += scivis-surface.qrc

OTHER_FILES += doc/src/* \
               doc/images/*

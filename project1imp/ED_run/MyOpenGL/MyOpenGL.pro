QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyOpenGL
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
    myglwidget.cpp \
    main5cpp.cpp \
    threeto2main.cpp \
    orthographic.cpp \
    orthographic_yz.cpp \
    orthographic_xz.cpp \
    classes.cpp \
    isometric.cpp

HEADERS  += window.h \
    myglwidget.h \
    main5cpp.h \
    main_choice.h \
    ../build-MyOpenGL-Desktop_Qt_5_0_2_GCC_64bit-Debug/ui_window.h \
    threeto2main.h \
    orthographic.h \
    orthographic_xz.h \
    classes.h \
    orthographic_yz.h \
    isometric.h\
    ui_window.h


LIBS          = -L/usr/lib/x86_64-linux-gnu/ -lm  -larmadillo
LIBS += \
    -LC:\Armadillo\lib_win64 \



FORMS    += \
    main_choice.ui \
    window.ui

DISTFILES += \
    MyOpenGL.pro.user.-1

QT       += core gui opengl
LIBS+= -lOpengl32 -glu32

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


LIBS          = -L/usr/lib/x86_64-linux-gnu/ -lm -lQtGui -larmadillo

FORMS    += \
    main_choice.ui

DISTFILES += \
    MyOpenGL.pro.user.-1

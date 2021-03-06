QT += widgets

HEADERS += \
    material.h \
    light.h \
    mainwindow.h \
    mesh.h \
    node.h \
    modelloader.h

SOURCES += \
    main.cpp \
    material.cpp \
    light.cpp \
    mainwindow.cpp \
    mesh.cpp \
    node.cpp \
    modelloader.cpp

RESOURCES = \
    application.qrc

LIBS += -lassimp

win32 {
    INCLUDEPATH += D:/Documenti-Mocciola/tmp/assimp/include
    LIBPATH     += D:/Documenti-Mocciola/tmp/assimp/bin32
}

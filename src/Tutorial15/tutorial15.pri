QT += opengl

HEADERS += \
    $$PWD/objects/scene.h \
    $$PWD/objects/abstractscene.h \
    $$PWD/ui/window.h \
    $$PWD/math/math3D.h \
    $$PWD/objects/pipeline.h \
    $$PWD/objects/camera.h

SOURCES += \
    $$PWD/objects/scene.cpp \
    $$PWD/objects/abstractscene.cpp \
    $$PWD/ui/window.cpp \
    $$PWD/objects/pipeline.cpp \
    $$PWD/math/math3D.cpp \
    $$PWD/objects/camera.cpp

RESOURCES += \
    $$PWD/resources.qrc

OTHER_FILES += \
    $$PWD/resources/shaders/basic.vert \
    $$PWD/resources/shaders/basic.frag


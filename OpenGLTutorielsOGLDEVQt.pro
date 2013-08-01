include( src/Tutorial15/tutorial15.pri )

QT += core gui widgets

RCC_DIR     = $$_PRO_FILE_PWD_/build/tmp/rcc
UI_DIR      = $$_PRO_FILE_PWD_/build/tmp/ui
MOC_DIR     = $$_PRO_FILE_PWD_/build/tmp/moc
OBJECTS_DIR = $$_PRO_FILE_PWD_/build/tmp/obj

CONFIG(debug, debug|release) {
    DESTDIR = $$_PRO_FILE_PWD_/build/debug
}
CONFIG(release, debug|release) {
    DESTDIR = $$_PRO_FILE_PWD_/build/release
}

SOURCES += \
    src/main.cpp

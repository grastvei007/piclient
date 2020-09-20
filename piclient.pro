QT -= gui
QT += widgets websockets xml
CONFIG += c++19 console
CONFIG -= app_bundle
TEMPLATE = app


release: TARGET = piclient
debug: TARGET = piclientd

DESTDIR = $$(DEV_BIN)
#/home/steini/Develop/bin

release: BUILDDIR = build/release
debug:   BUILDDIR = build/debug

OBJECTS_DIR = $$BUILDDIR/.obj
MOC_DIR = $$BUILDDIR/.moc
RCC_DIR = $$BUILDDIR/.qrc
UI_DIR = $$BUILDDIR/.ui

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBPATH = $$(DEV_LIBS)
message(lib path: $$LIBPATH)


if(debug){
LIBS += -L$$LIBPATH -ltagsystemd

}
else{
LIBS += -L$$LIBPATH -ltagsystem
}

INCLUDEPATH += $$(JUNE_ROOT)


linux {
    contains(QMAKE_HOST.arch, arm.*):{
       LIBS +=  -lwiringPi
	message(rasberry pi)
    }else{
        ...
    }
}

SOURCES += main.cpp \
    app.cpp \
    functions/heatereffect.cpp \
    functions/heaterfan.cpp \
    functions/heaterpreheat.cpp \
    functions/heaterpump.cpp \
    gpiopinfactory.cpp \
    heater.cpp \
    wiringpiwrapper.cpp

HEADERS += \
    app.h \
    factory.h \
    factorybase.h \
    functions/heatereffect.h \
    functions/heaterfan.h \
    functions/heaterpreheat.h \
    functions/heaterpump.h \
    gpiopinfactory.h \
    heater.h \
    wiringpiwrapper.h

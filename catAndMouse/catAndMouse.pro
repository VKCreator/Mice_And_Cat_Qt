QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    awardwidget.cpp \
    cat.cpp \
    main.cpp \
    mainwindow.cpp \
    mouse.cpp \
    widgetfordata.cpp

HEADERS += \
    awardwidget.h \
    cat.h \
    mainwindow.h \
    mouse.h \
    widgetfordata.h

FORMS += \
    awardwidget.ui \
    mainwindow.ui \
    widgetfordata.ui

TRANSLATIONS += \
    catAndMouse_de.ts \
    catAndMouse_tt.ts \
    catAndMouse_zh.ts \
    catAndMouse_en_US.ts \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc \
    catAndMouse.qrc \

win32:RC_ICONS += kisspng-computer-mouse-rat-computer-icons-rodent-animals-icon-5b0872416034c1.1807156815272801933941.ico

DISTFILES +=

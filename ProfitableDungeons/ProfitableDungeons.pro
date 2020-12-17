TEMPLATE = app TARGET = ProfitableDungeons
QT = core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    clickable_label.cpp \
    game_window.cpp \
    init.cpp \
    initial_window.cpp \
    tavern_dialog.cpp

HEADERS += \
    clickable_label.h \
    game_window.h \
    initial_window.h \
    tavern_dialog.h

FORMS += \
    game_window.ui \
    initial_window.ui \
    tavern_dialog.ui

RESOURCES += \
    resources.qrc

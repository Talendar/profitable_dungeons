TEMPLATE = app TARGET = ProfitableDungeons
QT = core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    building.cpp \
    building_dialog.cpp \
    buy_dialog.cpp \
    clickable_label.cpp \
    game_window.cpp \
    gold_purse.cpp \
    init.cpp \
    initial_window.cpp \
    semaphore.cpp

HEADERS += \
    building.h \
    building_dialog.h \
    buy_dialog.h \
    clickable_label.h \
    game_window.h \
    gold_purse.h \
    initial_window.h \
    semaphore.h

FORMS += \
    building_dialog.ui \
    buy_dialog.ui \
    game_window.ui \
    initial_window.ui

RESOURCES += \
    resources.qrc

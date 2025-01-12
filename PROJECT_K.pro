QT       += core gui sql  # модули осн ф-ии, граф интерфейс, база данных

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets  # виджеты

CONFIG += c++17

# для не компилирования кода, если устаревшие APIs.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    menu_bar/CustomButton.cpp \
    menu_bar/MenuBar.cpp\
    menu_bar/TopBar.cpp\
    table_view_model/DBTableViewModel.cpp\
    table_view_model/DBViewer.cpp\
    widget.cpp

HEADERS += \
    widget.h \
    menu_bar/CustomButton.h \
    menu_bar/MenuBar.h\
    menu_bar/TopBar.h\
    table_view_model/DBTableViewModel.h\
    table_view_model/DBViewer.h\
    includes.h

# путь установки для целевой платформы
qnx: target.path = /tmp/$${TARGET}/bin  # QNX
else: unix:!android: target.path = /opt/$${TARGET}/bin  # UNIX
!isEmpty(target.path): INSTALLS += target  # цель установки в проект, если путь установки не пустой

RESOURCES += \
    Resources/icons.qrc

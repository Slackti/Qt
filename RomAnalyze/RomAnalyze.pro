greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += \
    QHexPlugin/chunks.h \
    QHexPlugin/commands.h \
    QHexPlugin/qhexedit.h \
    QHexPlugin/QHexEditPlugin.h \
    mainwindow.h \
    optionsdialog.h \
    searchdialog.h

SOURCES += \
    QHexPlugin/chunks.cpp \
    QHexPlugin/commands.cpp \
    QHexPlugin/qhexedit.cpp \
    QHexPlugin/QHexEditPlugin.cpp \
    mainwindow.cpp \
    main.cpp \
    optionsdialog.cpp \
    searchdialog.cpp

RESOURCES += \
    romanalyze.qrc

FORMS += \
    optionsdialog.ui \
    searchdialog.ui

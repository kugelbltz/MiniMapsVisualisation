QT += widgets \
    location \
    quickwidgets \
    network \
    core

FORMS += \
    interface.ui \
    itineraire.ui

HEADERS += \
    interface.h \
    itineraire.h \
    nodeapirequest.h

SOURCES += \
    interface.cpp \
    main.cpp \
    itineraire.cpp \
    nodeapirequest.cpp \

DISTFILES += \
    map.qml \
    section.qml \

RESOURCES += \
    ressources.qrc

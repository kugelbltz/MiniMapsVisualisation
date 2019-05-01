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
    nodeapirequest.h \
    AlgoSources/Arc.h \
    AlgoSources/Cost.h \
    AlgoSources/Graph.h \
    AlgoSources/Json.h \
    AlgoSources/Label.h \
    AlgoSources/Node.h \
    AlgoSources/Position.h \
    AlgoSources/functions.h

SOURCES += \
    interface.cpp \
    main.cpp \
    itineraire.cpp \
    nodeapirequest.cpp \
    AlgoSources/Arc.cpp \
    AlgoSources/Cost.cpp \
    AlgoSources/Graph.cpp \
    AlgoSources/Json.cpp \
    AlgoSources/Label.cpp \
    AlgoSources/Node.cpp \
    AlgoSources/Position.cpp \
    AlgoSources/functions.cpp

DISTFILES += \
    map.qml \
    section.qml \

RESOURCES += \
    ressources.qrc

include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

QT       += sql
QT       -= gui

TARGET = lg-lib
TEMPLATE = lib

DEFINES += LGLIB_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += source

SOURCES += \
        source/controllers/clicommandcontroller.cpp                         \
        source/controllers/dricommandcontroller.cpp                         \
        source/controllers/vehcommandcontroller.cpp                         \
        source/controllers/tracommandcontroller.cpp                         \
        source/controllers/databasecontroller.cpp                           \
        source/controllers/mastercontroller.cpp                             \
        source/data/datadecorator.cpp                                       \
        source/data/entity.cpp                                              \
        source/data/intdecorator.cpp                                        \
        source/data/stringdecorator.cpp                                     \
        source/data/combooption.cpp                                         \
        source/framework/command.cpp                                        \
        source/models/destination.cpp                                       \
        source/models/address.cpp                                           \
        source/models/client.cpp                                            \
        source/models/clientsearch.cpp                                      \
        source/models/driver.cpp                                            \
        source/models/driversearch.cpp                                      \
        source/models/vehicle.cpp                                           \
        source/models/vehiclesearch.cpp                                     \
        source/models/travel.cpp                                            \
        source/models/travelsearch.cpp                                      \
        source/db_operations/getoptionfromtable.hpp                         \
        source/db_operations/master/getallstates.hpp                        \
        source/db_operations/client/findbyname.hpp                          \
        source/db_operations/client/updatebyid.hpp                          \
        source/db_operations/client/insert.hpp                              \
        source/db_operations/client/deletebyid.hpp                          \
        source/db_operations/driver/findbyname.hpp                          \
        source/db_operations/driver/updatebyid.hpp                          \
        source/db_operations/driver/insert.hpp                              \
        source/db_operations/driver/deletebyid.hpp                          \
        source/db_operations/vehicle/getoptmodelbybrandid.hpp               \
        source/db_operations/vehicle/findbybrand.hpp                        \
        source/db_operations/vehicle/updatebyid.hpp                         \
        source/db_operations/vehicle/insert.hpp                             \
        source/db_operations/vehicle/deletebyid.hpp                         \
        source/db_operations/travel/findbyclientname.hpp                    \
        source/db_operations/travel/getoptdrivers.hpp                       \
        source/db_operations/travel/getoptvehicles.hpp                      \
        source/db_operations/travel/updatebyid.hpp                          \
        source/db_operations/travel/insert.hpp                              \
        source/db_operations/travel/deletebyid.hpp

HEADERS += \
        source/lg-lib_global.h                                              \
        source/controllers/navigationcontroller.h                           \
        source/controllers/mastercontroller.h                               \
        source/controllers/clicommandcontroller.h                           \
        source/controllers/dricommandcontroller.h                           \
        source/controllers/vehcommandcontroller.h                           \
        source/controllers/tracommandcontroller.h                           \
        source/controllers/databasecontroller.h                             \
        source/data/datadecorator.h                                         \
        source/data/entity.h                                                \
        source/data/entitycollection.h                                      \
        source/data/intdecorator.h                                          \
        source/data/stringdecorator.h                                       \
        source/data/combooption.h                                           \
        source/framework/command.h                                          \
        source/models/address.h                                             \
        source/models/client.h                                              \
        source/models/clientsearch.h                                        \
        source/models/driver.h                                              \
        source/models/driversearch.h                                        \
        source/models/vehicle.h                                             \
        source/models/vehiclesearch.h                                       \
        source/models/destination.h                                         \
        source/models/travel.h                                              \
        source/models/travelsearch.h



DESTDIR = $$PWD/../binaries/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/build/$$DESTINATION_PATH/.qrc
UI_DIR =	$$PWD/build/$$DESTINATION_PATH/.ui

#!buid_pass:message(lg-lib project dir: $${DESTDIR})
#!buid_pass:message(Destination_path  value: $${DESTINATION_PATH})

unix {
    target.path = /usr/lib
    INSTALLS += target
}

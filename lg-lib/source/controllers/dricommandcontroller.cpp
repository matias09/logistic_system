#include "dricommandcontroller.h"
#include "db_operations/driver/deletebyid.hpp"
#include "db_operations/driver/updatebyid.hpp"
#include "db_operations/driver/insert.hpp"

#include <QList>
#include <QDateTime>

using namespace lg::framework;

namespace lg {
namespace controllers {

class DriCommandController::Implementation
{
public:
  Implementation(
            DriCommandController    *_driCommandController
           ,DatabaseController   *_databaseController
           ,NavigationController *_navigationController
           ,models::Driver       *_newDriver
           ,models::DriverSearch *_driverSearch )
    : driCommandController(_driCommandController)
    , databaseController(_databaseController)
    , navigationController(_navigationController)
    , newDriver(_newDriver)
    , driverSearch(_driverSearch)
  {
     Command *createDriverFillCommand = new Command(
       driCommandController, QChar( 0xf234 ), "New"
     );
     QObject::connect(
       createDriverFillCommand, &Command::executed,
       driCommandController, &DriCommandController::onCreateDriverFillExecuted
     );

     Command *createDriverSaveCommand = new Command(
       driCommandController, QChar(  0xf0c7 ), "Save"
     );
     QObject::connect(
       createDriverSaveCommand, &Command::executed,
       driCommandController, &DriCommandController::onCreateDriverSaveExecuted
     );
     createDriverVIewContextCommands.append( createDriverSaveCommand );

     Command *findDriverSearchCommand = new Command(
      driCommandController, QChar(  0xf002 ), "Search"
     );
     QObject::connect(
       findDriverSearchCommand, &Command::executed,
       driCommandController, &DriCommandController::onFindDriverViewContextCommands
     );
     findDriverViewContextCommands.append( findDriverSearchCommand );
     findDriverViewContextCommands.append( createDriverFillCommand );


     Command *editDriverSaveCommand = new Command(
      driCommandController, QChar(  0xf0c7 ), "Edit"
     );
     QObject::connect(
       editDriverSaveCommand, &Command::executed,
       driCommandController, &DriCommandController::onEditDriverSaveExecuted
     );
     editDriverViewContextCommands.append( editDriverSaveCommand );


     Command *editDriverDeleteCommand = new Command(
      driCommandController, QChar(  0xf235 ), "Delete"
     );
     QObject::connect(
       editDriverDeleteCommand, &Command::executed,
       driCommandController, &DriCommandController::onEditDriverDeleteExecuted
     );
     editDriverViewContextCommands.append( editDriverDeleteCommand );
  }

  DriCommandController *driCommandController{nullptr};

  QList<Command*> createDriverVIewContextCommands{};
  QList<Command*> findDriverViewContextCommands{};
  QList<Command*> editDriverViewContextCommands{};

  DatabaseController   *databaseController{nullptr};
  NavigationController *navigationController{nullptr};

  models::Driver       *newDriver{nullptr};
  models::Driver       *selectedDriver{nullptr};
  models::DriverSearch *driverSearch{nullptr};
};

DriCommandController::DriCommandController(
            QObject *parent
           ,DatabaseController   *databaseController
           ,NavigationController *navigationController
           ,models::Driver       *newDriver
           ,models::DriverSearch *driverSearch )
   : QObject(parent)
{
  implementation.reset( new Implementation(this
                                          ,databaseController
                                          ,navigationController
                                          ,newDriver
                                          ,driverSearch) );
}

DriCommandController::~DriCommandController() {}

void DriCommandController::setSelectedDriver(models::Driver *driver)
{
  implementation->selectedDriver = driver;
}

QQmlListProperty<Command>
DriCommandController::ui_createDriverViewContextCommands()
{
   return QQmlListProperty<Command>(
            this,
            implementation->createDriverVIewContextCommands );
}

void DriCommandController::onCreateDriverFillExecuted()
{
  implementation->navigationController->goCreateDriverView();
}

void DriCommandController::onCreateDriverSaveExecuted()
{
  bool r = Insert::call(implementation->newDriver->toJson()
                     ,*(implementation->databaseController) );

  if (r) {
    implementation->driverSearch->searchText()
                  ->setValue( implementation->newDriver->name->value() );
    implementation->driverSearch->search();
    implementation->navigationController->goFindDriverView();
  } else {
    implementation->navigationController->goDashboardView();
  }
}

QQmlListProperty<Command>
DriCommandController::ui_findDriverViewContextCommands()
{
   return QQmlListProperty<Command>(
            this,
            implementation->findDriverViewContextCommands );
}

void DriCommandController::onFindDriverViewContextCommands()
{
  implementation->driverSearch->search();
}


QQmlListProperty<Command>
DriCommandController::ui_editDriverViewContextCommands()
{
   return QQmlListProperty<Command>(
            this,
            implementation->editDriverViewContextCommands );
}

void DriCommandController::onEditDriverSaveExecuted()
{
  bool r = UpdateById::call( implementation->selectedDriver->toJson()
                          ,  implementation->selectedDriver->id()
                          ,*(implementation->databaseController) );

  if ( r ) {
    implementation->selectedDriver->reset();

    implementation->driverSearch->search();
    implementation->navigationController->goFindDriverView();
  }
}

QQmlListProperty<Command>
DriCommandController::ui_deleteDriverViewContextCommands()
{
   return QQmlListProperty<Command>(
            this,
            implementation->editDriverViewContextCommands );
}

void DriCommandController::onEditDriverDeleteExecuted()
{
  QString err = "";
  bool r = DeleteById::call( err
                          ,  implementation->selectedDriver->id()
                          ,*(implementation->databaseController) );
  if ( r ) {
    implementation->selectedDriver = nullptr;

    implementation->driverSearch->search();
    implementation->navigationController->goDashboardView();
  } else {
    implementation->selectedDriver->err->setValue(err);
  }
}

} // constrollers
} // lg

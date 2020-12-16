#include "dricommandcontroller.h"
#include "db_operations/driver/deletebyid.hpp"
#include "db_operations/driver/updatebyid.hpp"
#include "db_operations/driver/insert.hpp"

#include <QList>
#include <QDateTime>

#include <iostream>

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
       driCommandController, QChar( 0xf234 ), "Nuevo"
     );
     QObject::connect(
       createDriverFillCommand, &Command::executed,
       driCommandController, &DriCommandController::onCreateDriverFillExecuted
     );

     Command *createDriverSaveCommand = new Command(
       driCommandController, QChar(  0xf0c7 ), "Guardar"
     );
     QObject::connect(
       createDriverSaveCommand, &Command::executed,
       driCommandController, &DriCommandController::onCreateDriverSaveExecuted
     );
     createDriverVIewContextCommands.append( createDriverSaveCommand );

     Command *findDriverSearchCommand = new Command(
      driCommandController, QChar(  0xf002 ), "Buscar"
     );
     QObject::connect(
       findDriverSearchCommand, &Command::executed,
       driCommandController, &DriCommandController::onFindDriverViewContextCommands
     );
     findDriverViewContextCommands.append( findDriverSearchCommand );
     findDriverViewContextCommands.append( createDriverFillCommand );


     Command *editDriverSaveCommand = new Command(
      driCommandController, QChar(  0xf0c7 ), "Editar"
     );
     QObject::connect(
       editDriverSaveCommand, &Command::executed,
       driCommandController, &DriCommandController::onEditDriverSaveExecuted
     );
     editDriverViewContextCommands.append( editDriverSaveCommand );


     Command *editDriverDeleteCommand = new Command(
      driCommandController, QChar(  0xf235 ), "Borrar"
     );
     QObject::connect(
       editDriverDeleteCommand, &Command::executed,
       driCommandController, &DriCommandController::onEditDriverDeleteExecuted
     );
     editDriverViewContextCommands.append( editDriverDeleteCommand );
  }

  bool validateBusinessRules(QString &err, models::Driver &d) const
  {
    if (QDateTime::currentDateTime().toSecsSinceEpoch() + 1
        >
        QDateTime::fromString(d.lic_cad->value()
                            , Qt::ISODate).toSecsSinceEpoch() 
  ) {
      err.append("La Fecha de la Licencia del Conductor debe ser mayor "
                 "a la fecha actual.");
      return false;
    }

    return true;
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
  std::cout << "You executed the Create New Driver Command!" << std::endl;
  implementation->navigationController->goCreateDriverView();
}

void DriCommandController::onCreateDriverSaveExecuted()
{
  std::cout << "You executed the Save Command!" << std::endl;

  QString err = "";
  bool r = implementation->validateBusinessRules(err
                                                ,*(implementation->newDriver));
  if (not r) {
    std::cout << "Error Saving Driver: \n \t"
              << "Desc: " << err.toStdString()
              << std::endl;
    implementation->newDriver->err->setValue(err);
    return;
  }

  r = Insert::call(implementation->newDriver->toJson()
                     ,*(implementation->databaseController) );

  if (r) {
    std::cout << "New Driver Saved!" << std::endl;

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
  std::cout << "You executed the Search Command!" << std::endl;
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
  std::cout << "You executed the Edit Command!" << std::endl;

  QString err = "";
  bool r = implementation->validateBusinessRules(err
                                            ,*(implementation->selectedDriver));
  if (not r) {
    std::cout << "Error Saving Driver: \n \t"
              << "Desc: " << err.toStdString()
              << std::endl;
    implementation->selectedDriver->err->setValue(err);
    return;
  }

  r = UpdateById::call( implementation->selectedDriver->toJson()
                          ,  implementation->selectedDriver->id()
                          ,*(implementation->databaseController) );

  if ( r ) {
    std::cout << "Driver Updated"     << std::endl;

    implementation->selectedDriver->reset();

    implementation->driverSearch->search();
    implementation->navigationController->goFindDriverView();
  } else {
    std::cout << "Driver NOT Updated" << std::endl;
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
  std::cout << "You executed the Delete Command!" << std::endl;

  QString err = "";
  bool r = DeleteById::call( err
                          ,  implementation->selectedDriver->id()
                          ,*(implementation->databaseController) );
  if ( r ) {
    std::cout << "Driver deleted" << std::endl;

    implementation->selectedDriver = nullptr;

    implementation->driverSearch->search();
    implementation->navigationController->goDashboardView();
  } else {
    std::cout << "Driver NOT Erased" << std::endl;
    implementation->selectedDriver->err->setValue(err);
  }
}

} // constrollers
} // lg

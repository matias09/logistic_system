#include "tracommandcontroller.h"

#include "db_operations/getoptionfromtable.hpp"

#include "db_operations/travel/deletebyid.hpp"
#include "db_operations/travel/updatebyid.hpp"
#include "db_operations/travel/insert.hpp"
#include "db_operations/travel/getoptunblocked.hpp"

#include <QList>

#include <iostream>

using namespace lg::framework;

namespace lg {
namespace controllers {

class TraCommandController::Implementation
{
public:
  Implementation(
            TraCommandController *_traCommandController
           ,DatabaseController   *_databaseController
           ,NavigationController *_navigationController
           ,models::Travel       *_newTravel
           ,models::TravelSearch *_travelSearch )
    : traCommandController(_traCommandController)
    , databaseController(_databaseController)
    , navigationController(_navigationController)
    , newTravel(_newTravel)
    , travelSearch(_travelSearch)
  {
     Command *createTravelFillCommand = new Command(
       traCommandController, QChar( 0xf234 ), "Nuevo"
     );
     QObject::connect(
       createTravelFillCommand, &Command::executed,
       traCommandController, &TraCommandController::onCreateTravelFillExecuted
     );

     Command *createTravelSaveCommand = new Command(
       traCommandController, QChar(  0xf0c7 ), "Guardar"
     );
     QObject::connect(
       createTravelSaveCommand, &Command::executed,
       traCommandController, &TraCommandController::onCreateTravelSaveExecuted
     );
     createTravelVIewContextCommands.append( createTravelSaveCommand );

     Command *findTravelSearchCommand = new Command(
      traCommandController, QChar(  0xf002 ), "Buscar"
     );
     QObject::connect(
       findTravelSearchCommand, &Command::executed,
       traCommandController, &TraCommandController::onFindTravelViewContextCommands
     );
     findTravelViewContextCommands.append( findTravelSearchCommand );
     findTravelViewContextCommands.append( createTravelFillCommand );


     Command *editTravelSaveCommand = new Command(
      traCommandController, QChar(  0xf0c7 ), "Editar"
     );
     QObject::connect(
       editTravelSaveCommand, &Command::executed,
       traCommandController, &TraCommandController::onEditTravelSaveExecuted
     );
     editTravelViewContextCommands.append( editTravelSaveCommand );


     Command *editTravelDeleteCommand = new Command(
      traCommandController, QChar(  0xf235 ), "Anular"
     );
     QObject::connect(
       editTravelDeleteCommand, &Command::executed,
       traCommandController, &TraCommandController::onEditTravelDeleteExecuted
     );
     editTravelViewContextCommands.append( editTravelDeleteCommand );

     updateClients();
     updateDrivers();
     updateVehicles();
  }

  void updateClients()
  {
    clients.clear();
    clients  = GetOptionFromTable::call("clients"
                                      ,*(traCommandController)
                                      ,*(databaseController) );
  }

  void updateDrivers()
  {
     drivers.clear();
     drivers  = GetOptUnblocked::call("drivers"
                                    ,*(traCommandController)
                                    ,*(databaseController) );
  }

  void updateVehicles()
  {
     vehicles.clear();
     vehicles = GetOptUnblocked::call("vehicles"
                                    ,*(traCommandController)
                                    ,*(databaseController) );
  }



  TraCommandController *traCommandController{nullptr};

  QList<Command*> createTravelVIewContextCommands{};
  QList<Command*> findTravelViewContextCommands{};
  QList<Command*> editTravelViewContextCommands{};

  QList<data::ComboOption*> clients{};
  QList<data::ComboOption*> drivers{};
  QList<data::ComboOption*> vehicles{};

  DatabaseController   *databaseController{nullptr};
  NavigationController *navigationController{nullptr};

  models::Travel       *newTravel{nullptr};
  models::Travel       *selectedTravel{nullptr};
  models::TravelSearch *travelSearch{nullptr};
};

TraCommandController::TraCommandController(
            QObject *parent
           ,DatabaseController   *databaseController
           ,NavigationController *navigationController
           ,models::Travel       *newTravel
           ,models::TravelSearch *travelSearch )
   : QObject(parent)
{
  implementation.reset( new Implementation(this
                                          ,databaseController
                                          ,navigationController
                                          ,newTravel
                                          ,travelSearch) );
}

TraCommandController::~TraCommandController() {}

void TraCommandController::setSelectedTravel(models::Travel *travel)
{
  implementation->selectedTravel = travel;
}

QQmlListProperty<Command>
TraCommandController::ui_createTravelViewContextCommands()
{
   return QQmlListProperty<Command>(
            this,
            implementation->createTravelVIewContextCommands );
}

void TraCommandController::onCreateTravelFillExecuted()
{
  std::cout << "You executed the Create New Travel Command!" << std::endl;


  implementation->navigationController->goCreateTravelView();
}

void TraCommandController::onCreateTravelSaveExecuted()
{
  std::cout << "You executed the Save Command!" << std::endl;

  QString err = "";
  bool r = Insert::call(err
                     , implementation->newTravel->toJson()
                     ,*(implementation->databaseController) );

  if (r) {
    std::cout << "New Travel Saved!" << std::endl;

    std::cout << "Value to search : "
              << implementation->newTravel->cli->value().toStdString()
              << std::endl;

    implementation->travelSearch->searchText()
                  ->setValue( implementation->newTravel->cli->value() );
    implementation->travelSearch->search();
    implementation->navigationController->goFindTravelView();
  } else {
    std::cout << "Error Saving Travel" << std::endl;
    implementation->newTravel->destiny->err->setValue(err);
  }
}

QQmlListProperty<data::ComboOption> TraCommandController::clients()
{
  implementation->updateClients();
  return QQmlListProperty<data::ComboOption>( this, implementation->clients );
}

QQmlListProperty<data::ComboOption> TraCommandController::drivers()
{
  implementation->updateDrivers();
  return QQmlListProperty<data::ComboOption>( this, implementation->drivers );
}

QQmlListProperty<data::ComboOption> TraCommandController::vehicles()
{
  implementation->updateVehicles();
  return QQmlListProperty<data::ComboOption>( this, implementation->vehicles );
}


QQmlListProperty<Command>
TraCommandController::ui_findTravelViewContextCommands()
{
  return QQmlListProperty<Command>(
          this,
          implementation->findTravelViewContextCommands );
}

void TraCommandController::onFindTravelViewContextCommands()
{
  std::cout << "You executed the Search Command!" << std::endl;
  implementation->travelSearch->search();
}


QQmlListProperty<Command>
TraCommandController::ui_editTravelViewContextCommands()
{
   return QQmlListProperty<Command>(
            this,
            implementation->editTravelViewContextCommands );
}

void TraCommandController::onEditTravelSaveExecuted()
{
  std::cout << "You executed the Edit Command!" << std::endl;

  QString err = "";
  bool r = UpdateById::call( err
                          ,  implementation->selectedTravel->toJson()
                          ,*(implementation->databaseController) );

  if ( r ) {
    std::cout << "Travel Updated"     << std::endl;
    implementation->travelSearch->searchText()
                  ->setValue( implementation->selectedTravel->reference->value() );
    implementation->travelSearch->search();
    implementation->navigationController->goFindTravelView();
  } else {
    std::cout << "Travel NOT Updated" << std::endl;
    implementation->selectedTravel->destiny->err->setValue(err);
  }
}


QQmlListProperty<Command>
TraCommandController::ui_deleteTravelViewContextCommands()
{
   return QQmlListProperty<Command>(
            this,
            implementation->editTravelViewContextCommands );
}

void TraCommandController::onEditTravelDeleteExecuted()
{
  std::cout << "You executed the Delete Command!" << std::endl;

  DeleteById::call(  implementation->selectedTravel->toJson()
                   , implementation->selectedTravel->id()
                   ,*(implementation->databaseController) );

  implementation->selectedTravel = nullptr;

  std::cout << "Travel deleted" << std::endl;

  implementation->travelSearch->search();
  implementation->navigationController->goDashboardView();
}

} // constrollers
} // lg

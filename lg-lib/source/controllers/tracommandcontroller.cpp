#include "tracommandcontroller.h"
#include "db_operations/travel/deletebyid.hpp"
#include "db_operations/travel/updatebyid.hpp"
#include "db_operations/travel/insert.hpp"

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
      traCommandController, QChar(  0xf235 ), "Borrar"
     );
     QObject::connect(
       editTravelDeleteCommand, &Command::executed,
       traCommandController, &TraCommandController::onEditTravelDeleteExecuted
     );
     editTravelViewContextCommands.append( editTravelDeleteCommand );
  }

  TraCommandController *traCommandController{nullptr};

  QList<Command*> createTravelVIewContextCommands{};
  QList<Command*> findTravelViewContextCommands{};
  QList<Command*> editTravelViewContextCommands{};

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

  bool r = Insert::call(implementation->newTravel->toJson()
                     ,*(implementation->databaseController) );

  if (r) {
    std::cout << "New Travel Saved!" << std::endl;

    implementation->travelSearch->searchText()
                  ->setValue( implementation->newTravel->reference->value() );
    implementation->travelSearch->search();
    implementation->navigationController->goFindTravelView();
  } else {
    implementation->navigationController->goDashboardView();
  }
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

  bool r = UpdateById::call( implementation->selectedTravel->toJson()
                          ,  implementation->selectedTravel->id()
                          ,*(implementation->databaseController) );

  if ( r ) {
    std::cout << "Travel Updated"     << std::endl;
  } else {
    std::cout << "Travel NOT Updated" << std::endl;
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

  DeleteById::call( implementation->selectedTravel->id()
                   ,*(implementation->databaseController) );

  implementation->selectedTravel = nullptr;

  std::cout << "Travel deleted" << std::endl;

  implementation->travelSearch->search();
  implementation->navigationController->goDashboardView();
}

} // constrollers
} // lg

#include "tracommandcontroller.h"

#include "db_operations/getoptionfromtable.hpp"

#include "db_operations/travel/deletebyid.hpp"
#include "db_operations/travel/updatebyid.hpp"
#include "db_operations/travel/insert.hpp"
#include "db_operations/travel/getoptdrivers.hpp"
#include "db_operations/travel/getoptvehicles.hpp"

#include <QList>
#include <QDateTime>

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
       traCommandController, QChar( 0xf234 ), "New"
     );
     QObject::connect(
       createTravelFillCommand, &Command::executed,
       traCommandController, &TraCommandController::onCreateTravelFillExecuted
     );

     Command *createTravelSaveCommand = new Command(
       traCommandController, QChar(  0xf0c7 ), "Save"
     );
     QObject::connect(
       createTravelSaveCommand, &Command::executed,
       traCommandController, &TraCommandController::onCreateTravelSaveExecuted
     );
     createTravelVIewContextCommands.append( createTravelSaveCommand );

     Command *findTravelSearchCommand = new Command(
      traCommandController, QChar(  0xf002 ), "Search"
     );
     QObject::connect(
       findTravelSearchCommand, &Command::executed,
       traCommandController, &TraCommandController::onFindTravelViewContextCommands
     );
     findTravelViewContextCommands.append( findTravelSearchCommand );
     findTravelViewContextCommands.append( createTravelFillCommand );


     Command *editTravelSaveCommand = new Command(
      traCommandController, QChar(  0xf0c7 ), "Edit"
     );
     QObject::connect(
       editTravelSaveCommand, &Command::executed,
       traCommandController, &TraCommandController::onEditTravelSaveExecuted
     );
     editTravelViewContextCommands.append( editTravelSaveCommand );


     Command *editTravelDeleteCommand = new Command(
      traCommandController, QChar(  0xf235 ), "Abort"
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
     drivers  = GetOptDriver::call(*(traCommandController)
                                  ,*(databaseController) );
  }

  void updateVehicles()
  {
     vehicles.clear();
     vehicles = GetOptVehicle::call(*(traCommandController)
                                   ,*(databaseController) );
  }

  bool validateBusinessRules(QString &err, models::Travel &t) const
  {
    if (t.id_cli->value() == 0) {
      err.append("The Client can't be empty");
      return false;
    }

    if (t.destiny->id_dri->value() == 0) {
      err.append("The Driver can't be empty");
      return false;
    }

    if (t.destiny->id_veh->value() == 0) {
      err.append("The Vehicle can't be empty");
      return false;
    }

    if (QDateTime::fromString(t.sta_date->value()
                            , Qt::ISODate).toSecsSinceEpoch() + 1
        >
        QDateTime::fromString(t.destiny->arr_date->value()
                            , Qt::ISODate).toSecsSinceEpoch()
   ) {
      err.append("The start Date must be lower than the arrival Date");
      return false;
    }

    if (t.ended->value() == 1) {
      if (QDateTime::fromString(t.destiny->arr_date->value()
                              , Qt::ISODate).toSecsSinceEpoch()
          >
          QDateTime::fromString(t.fin_date->value()
                              , Qt::ISODate).toSecsSinceEpoch()
     ) {
        err.append("The last arrival Date must be equal or lower "
                   "than the end Date.");
        return false;
      }
    }

    return true;
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
  implementation->navigationController->goCreateTravelView();
}

void TraCommandController::onCreateTravelSaveExecuted()
{
  QString err = "";
  bool r = implementation->validateBusinessRules(err
                                                ,*(implementation->newTravel));
  if (not r) {
    implementation->newTravel->destiny->err->setValue(err);
    return;
  }

  r = Insert::call(err
                 , implementation->newTravel->toJson()
                 ,*(implementation->databaseController) );

  if (r) {
    implementation->travelSearch->searchText()
                  ->setValue( implementation->newTravel->cli->value() );

    implementation->newTravel->reset();

    implementation->travelSearch->search();
    implementation->navigationController->goFindTravelView();
  } else {
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
  implementation->travelSearch->search();
}


QQmlListProperty<Command>
TraCommandController::ui_editTravelViewContextCommands()
{
    if (   implementation->selectedTravel->ended->value()    == 0
        && implementation->selectedTravel->canceled->value() == 0) {
     return QQmlListProperty<Command>(
              this,
              implementation->editTravelViewContextCommands );
    }

   return {};
}

void TraCommandController::onEditTravelSaveExecuted()
{
  QString err = "";
  bool r = implementation->validateBusinessRules(err
                                          ,*(implementation->selectedTravel));
  if (not r) {
    implementation->selectedTravel->destiny->err->setValue(err);
    return;
  }

   r = UpdateById::call( err
                      ,  implementation->selectedTravel->toJson()
                      ,*(implementation->databaseController) );

  if ( r ) {
    implementation->travelSearch->searchText()
                  ->setValue( implementation->selectedTravel->cli->value() );

    implementation->selectedTravel->reset();

    implementation->travelSearch->search();
    implementation->navigationController->goFindTravelView();
  } else {
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
  DeleteById::call(  implementation->selectedTravel->toJson()
                   , implementation->selectedTravel->id()
                   ,*(implementation->databaseController) );

  implementation->selectedTravel = nullptr;

  implementation->travelSearch->search();
  implementation->navigationController->goDashboardView();
}

} // constrollers
} // lg

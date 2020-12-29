#include "vehcommandcontroller.h"

#include "db_operations/getoptionfromtable.hpp"

#include "db_operations/vehicle/deletebyid.hpp"
#include "db_operations/vehicle/updatebyid.hpp"
#include "db_operations/vehicle/insert.hpp"
#include "db_operations/vehicle/getoptmodelbybrandid.hpp"

#include "data/combooption.h"

#include <QList>
#include <QDateTime>

using namespace lg::framework;

namespace lg {
namespace controllers {

class VehCommandController::Implementation
{
public:
  Implementation(
            VehCommandController *_vehCommandController
           ,DatabaseController   *_databaseController
           ,NavigationController *_navigationController
           ,models::Vehicle       *_newVehicle
           ,models::VehicleSearch *_vehicleSearch )
    : vehCommandController(_vehCommandController)
    , databaseController(_databaseController)
    , navigationController(_navigationController)
    , newVehicle(_newVehicle)
    , vehicleSearch(_vehicleSearch)
  {
     Command *createVehicleFillCommand = new Command(
       vehCommandController, QChar( 0xf234 ), "New"
     );
     QObject::connect(
       createVehicleFillCommand, &Command::executed,
       vehCommandController, &VehCommandController::onCreateVehicleFillExecuted
     );

     Command *createVehicleSaveCommand = new Command(
       vehCommandController, QChar(  0xf0c7 ), "Save"
     );
     QObject::connect(
       createVehicleSaveCommand, &Command::executed,
       vehCommandController, &VehCommandController::onCreateVehicleSaveExecuted
     );
     createVehicleVIewContextCommands.append( createVehicleSaveCommand );

     Command *findVehicleSearchCommand = new Command(
      vehCommandController, QChar(  0xf002 ), "Search"
     );
     QObject::connect(
       findVehicleSearchCommand, &Command::executed,
       vehCommandController, &VehCommandController::onFindVehicleViewContextCommands
     );
     findVehicleViewContextCommands.append( findVehicleSearchCommand );
     findVehicleViewContextCommands.append( createVehicleFillCommand );


     Command *editVehicleSaveCommand = new Command(
      vehCommandController, QChar(  0xf0c7 ), "Edit"
     );
     QObject::connect(
       editVehicleSaveCommand, &Command::executed,
       vehCommandController, &VehCommandController::onEditVehicleSaveExecuted
     );
     editVehicleViewContextCommands.append( editVehicleSaveCommand );


     Command *editVehicleDeleteCommand = new Command(
      vehCommandController, QChar(  0xf235 ), "Delete"
     );
     QObject::connect(
       editVehicleDeleteCommand, &Command::executed,
       vehCommandController, &VehCommandController::onEditVehicleDeleteExecuted
     );
     editVehicleViewContextCommands.append( editVehicleDeleteCommand );


     updateTypes();
     updateBrands();
     updateModels();
  }

  void updateTypes()
  {
    types = GetOptionFromTable::call( "vehicle_types"
                                     ,*(vehCommandController)
                                     ,*(databaseController) );
  }

  void updateBrands()
  {
    brands = GetOptionFromTable::call( "brands"
                                      ,*(vehCommandController)
                                      ,*(databaseController) );
  }

  void updateModels(const int idbrand = 1)
  {
    models = GetOptModelByBrandId::call( idbrand
                                      ,*(vehCommandController)
                                      ,*(databaseController) );
  }

  VehCommandController *vehCommandController{nullptr};

  QList<Command*> createVehicleVIewContextCommands{};
  QList<Command*> findVehicleViewContextCommands{};
  QList<Command*> editVehicleViewContextCommands{};

  QList<data::ComboOption*> types{};
  QList<data::ComboOption*> brands{};
  QList<data::ComboOption*> models{};

  DatabaseController   *databaseController{nullptr};
  NavigationController *navigationController{nullptr};

  models::Vehicle       *newVehicle{nullptr};
  models::Vehicle       *selectedVehicle{nullptr};
  models::VehicleSearch *vehicleSearch{nullptr};
};

VehCommandController::VehCommandController(
            QObject *parent
           ,DatabaseController   *databaseController
           ,NavigationController *navigationController
           ,models::Vehicle       *newVehicle
           ,models::VehicleSearch *vehicleSearch )
   : QObject(parent)
{
  implementation.reset( new Implementation(this
                                          ,databaseController
                                          ,navigationController
                                          ,newVehicle
                                          ,vehicleSearch) );
}

VehCommandController::~VehCommandController() {}

void VehCommandController::setSelectedVehicle(models::Vehicle *vehicle)
{
  implementation->selectedVehicle = vehicle;
}

QQmlListProperty<data::ComboOption> VehCommandController::types()
{
   return QQmlListProperty<data::ComboOption>(
      this, implementation->types );
}

QQmlListProperty<data::ComboOption> VehCommandController::brands()
{
   return QQmlListProperty<data::ComboOption>(
      this, implementation->brands );
}

QQmlListProperty<data::ComboOption> VehCommandController::models()
{
   return QQmlListProperty<data::ComboOption>(
      this, implementation->models );
}

QQmlListProperty<Command>
VehCommandController::ui_createVehicleViewContextCommands()
{
   return QQmlListProperty<Command>(
      this,
      implementation->createVehicleVIewContextCommands );
}

void VehCommandController::onCreateVehicleFillExecuted()
{
  implementation->navigationController->goCreateVehicleView();
}

void VehCommandController::onCreateVehicleSaveExecuted()
{
  bool r = Insert::call(implementation->newVehicle->toJson()
                     ,*(implementation->databaseController) );

  if (r) {
    implementation->vehicleSearch->searchText()
                  ->setValue( implementation->newVehicle->name->value() );
    implementation->vehicleSearch->search();
    implementation->navigationController->goFindVehicleView();
  } else {
    implementation->navigationController->goDashboardView();
  }
}

QQmlListProperty<Command>
VehCommandController::ui_findVehicleViewContextCommands()
{
   return QQmlListProperty<Command>(
      this,
      implementation->findVehicleViewContextCommands );
}

void VehCommandController::onFindVehicleViewContextCommands()
{
  implementation->vehicleSearch->search();
}

void VehCommandController::onBrandsChanged(const int bid)
{
  implementation->updateModels(bid);
  models();
}

QQmlListProperty<Command>
VehCommandController::ui_editVehicleViewContextCommands()
{
   return QQmlListProperty<Command>(
      this,
      implementation->editVehicleViewContextCommands );
}

void VehCommandController::onEditVehicleSaveExecuted()
{
  bool r = UpdateById::call( implementation->selectedVehicle->toJson()
                     ,  implementation->selectedVehicle->id()
                     ,*(implementation->databaseController) );

  if ( r ) {
    implementation->selectedVehicle->reset();

    implementation->vehicleSearch->search();
    implementation->navigationController->goFindVehicleView();
  }
}

QQmlListProperty<Command>
VehCommandController::ui_deleteVehicleViewContextCommands()
{
   return QQmlListProperty<Command>(
            this,
            implementation->editVehicleViewContextCommands );
}

void VehCommandController::onEditVehicleDeleteExecuted()
{
  QString err = "";
  bool r = DeleteById::call( err
                          ,  implementation->selectedVehicle->id()
                          ,*(implementation->databaseController) );
  if ( r ) {
    implementation->selectedVehicle = nullptr;

    implementation->vehicleSearch->search();
    implementation->navigationController->goDashboardView();
  } else {
    implementation->selectedVehicle->err->setValue(err);
  }
}

// Signals

} // constrollers
} // lg

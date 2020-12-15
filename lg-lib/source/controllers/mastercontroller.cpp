#include "mastercontroller.h"
#include "db_operations/master/getallstates.hpp"

namespace lg {
namespace controllers {

class MasterController::Implementation
{
public:
  Implementation(MasterController* _masterController)
    : masterController(_masterController)
   {
      databaseController   = new DatabaseController();
      navigationController = new NavigationController(masterController);

      newClient    = new models::Client(masterController);
      clientSearch = new models::ClientSearch(masterController
                                             ,databaseController);

      cliCommandController = new CliCommandController(masterController
                                                     ,databaseController
                                                     ,navigationController
                                                     ,newClient
                                                     ,clientSearch);

      newDriver    = new models::Driver(masterController);
      driverSearch = new models::DriverSearch(masterController
                                             ,databaseController);

      driCommandController = new DriCommandController(masterController
                                                     ,databaseController
                                                     ,navigationController
                                                     ,newDriver
                                                     ,driverSearch);

      newVehicle   = new models::Vehicle(masterController);
      vehicleSearch = new models::VehicleSearch(masterController
                                              ,databaseController);

      vehCommandController = new VehCommandController(masterController
                                                     ,databaseController
                                                     ,navigationController
                                                     ,newVehicle
                                                     ,vehicleSearch);

      newTravel   = new models::Travel(masterController);
      travelSearch = new models::TravelSearch(masterController
                                              ,databaseController);

      traCommandController = new TraCommandController(masterController
                                                     ,databaseController
                                                     ,navigationController
                                                     ,newTravel
                                                     ,travelSearch);

      cl =  GetAllStates::call(*(masterController), *(databaseController));
   }

   MasterController        *masterController{nullptr};
   NavigationController    *navigationController{nullptr};
   CliCommandController    *cliCommandController{nullptr};
   DriCommandController    *driCommandController{nullptr};
   VehCommandController    *vehCommandController{nullptr};
   TraCommandController    *traCommandController{nullptr};
   DatabaseController      *databaseController{nullptr};

   models::Client       *newClient{nullptr};
   models::ClientSearch *clientSearch{nullptr};

   models::Driver       *newDriver{nullptr};
   models::DriverSearch *driverSearch{nullptr};

   models::Vehicle       *newVehicle{nullptr};
   models::VehicleSearch *vehicleSearch{nullptr};

   models::Travel       *newTravel{nullptr};
   models::TravelSearch *travelSearch{nullptr};

   QList<data::ComboOption*> cl;
};

MasterController::MasterController(QObject* parent)
  : QObject(parent)
{
  implementation.reset( new Implementation(this) );
}

MasterController::~MasterController() {}

QQmlListProperty<data::ComboOption>
MasterController::states()
{
   return QQmlListProperty<data::ComboOption>(this, implementation->cl);
}

NavigationController* MasterController::navigationController()
{
  return  implementation->navigationController;
}

models::Client* MasterController::newClient()
{
  return  implementation->newClient;
}

models::ClientSearch* MasterController::clientSearch()
{
  return  implementation->clientSearch;
}

models::Driver* MasterController::newDriver()
{
  return  implementation->newDriver;
}

models::DriverSearch* MasterController::driverSearch()
{
  return  implementation->driverSearch;
}

models::Vehicle* MasterController::newVehicle()
{
  return  implementation->newVehicle;
}

models::VehicleSearch* MasterController::vehicleSearch()
{
  return  implementation->vehicleSearch;
}

models::Travel* MasterController::newTravel()
{
  return  implementation->newTravel;
}

models::TravelSearch* MasterController::travelSearch()
{
  return  implementation->travelSearch;
}

CliCommandController* MasterController::cliCommandController()
{
  return  implementation->cliCommandController;
}

DriCommandController* MasterController::driCommandController()
{
  return  implementation->driCommandController;
}

VehCommandController* MasterController::vehCommandController()
{
  return  implementation->vehCommandController;
}

TraCommandController* MasterController::traCommandController()
{
  return  implementation->traCommandController;
}

DatabaseController* MasterController::databaseController()
{
  return  implementation->databaseController;
}

// Slots Imp
void MasterController::selectClient(lg::models::Client *client)
{
  implementation->cliCommandController->setSelectedClient(client);
  implementation->navigationController->goEditClientView(client);
}

void MasterController::selectDriver(lg::models::Driver *driver)
{
  implementation->driCommandController->setSelectedDriver(driver);
  implementation->navigationController->goEditDriverView(driver);
}

void MasterController::selectVehicle(lg::models::Vehicle *vehicle)
{
  implementation->vehCommandController->setSelectedVehicle(vehicle);
  implementation->navigationController->goEditVehicleView(vehicle);
}

void MasterController::selectTravel(lg::models::Travel *travel)
{
  implementation->traCommandController->setSelectedTravel(travel);
  implementation->navigationController->goEditTravelView(travel);
}

} // controllers
} // lg

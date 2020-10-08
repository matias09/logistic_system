#include "mastercontroller.h"

namespace lg {
namespace controllers {

class MasterController::Implementation
{
public:
  Implementation(MasterController* _masterController)
    : masterController(_masterController)
   {
      databaseController   = new DatabaseController(masterController);
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
   }

   MasterController* masterController{nullptr};
   NavigationController* navigationController{nullptr};
   CliCommandController* cliCommandController{nullptr};
   DriCommandController* driCommandController{nullptr};
   DatabaseController* databaseController{nullptr};

   models::Client *newClient{nullptr};
   models::ClientSearch *clientSearch{nullptr};

   models::Driver *newDriver{nullptr};
   models::DriverSearch *driverSearch{nullptr};
};

MasterController::MasterController(QObject* parent)
  : QObject(parent)
{
  implementation.reset( new Implementation(this) );
}

MasterController::~MasterController() {}

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

CliCommandController* MasterController::cliCommandController()
{
  return  implementation->cliCommandController;
}

DriCommandController* MasterController::driCommandController()
{
  return  implementation->driCommandController;
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

} // controllers
} // lg

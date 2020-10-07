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
   }

   MasterController* masterController{nullptr};
   NavigationController* navigationController{nullptr};
   CliCommandController* cliCommandController{nullptr};
   DatabaseController* databaseController{nullptr};

   models::Client *newClient{nullptr};
   models::ClientSearch *clientSearch{nullptr};
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

CliCommandController* MasterController::cliCommandController()
{
  return  implementation->cliCommandController;
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

} // controllers
} // lg

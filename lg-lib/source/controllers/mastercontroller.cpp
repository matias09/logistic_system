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

      commandController = new CommandController(masterController
                                               ,databaseController
                                               ,navigationController
                                               ,newClient
                                               ,clientSearch);
   }

   MasterController* masterController{nullptr};
   NavigationController* navigationController{nullptr};
   CommandController* commandController{nullptr};
   DatabaseController* databaseController{nullptr};

   models::Client *newClient{nullptr};
   models::ClientSearch *clientSearch{nullptr};

   QString welcomeMessage = "This is MasterController to Major Tom";
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

CommandController* MasterController::commandController()
{
  return  implementation->commandController;
}

DatabaseController* MasterController::databaseController()
{
  return  implementation->databaseController;
}

const QString& MasterController::welcomeMessage() const
{
  return implementation->welcomeMessage;
}

// Slots Imp
void MasterController::selectClient(lg::models::Client *client)
{
  implementation->commandController->setSelectedClient(client);
  implementation->navigationController->goEditClientView(client);
}

} // controllers
} // lg

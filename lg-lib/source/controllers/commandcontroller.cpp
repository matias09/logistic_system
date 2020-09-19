#include "commandcontroller.h"

#include <QList>

#include <iostream>

using namespace lg::framework;

namespace lg {
namespace controllers {

class CommandController::Implementation
{
public:
  Implementation(
            CommandController    *_commandController
           ,IDatabaseController  *_databaseController
           ,NavigationController *_navigationController
           ,models::Client       *_newClient
           ,models::ClientSearch *_clientSearch )
    : commandController(_commandController)
    , databaseController(_databaseController)
    , navigationController(_navigationController)
    , newClient(_newClient)
    , clientSearch(_clientSearch)
  {
     Command *createClientSaveCommand = new Command(
       commandController, QChar(  0xf0c7 ), "Save"
     );
     QObject::connect(
       createClientSaveCommand, &Command::executed,
       commandController, &CommandController::onCreateClientSaveExecuted
     );
     createClientVIewContextCommands.append( createClientSaveCommand );


     Command *findClientSearchCommand = new Command(
      commandController, QChar(  0xf002 ), "Search"
     );
     QObject::connect(
       findClientSearchCommand, &Command::executed,
       commandController, &CommandController::onFindClientViewContextCommands
     );
     findClientViewContextCommands.append( findClientSearchCommand );


     Command *editClientSaveCommand = new Command(
      commandController, QChar(  0xf0c7 ), "Save"
     );
     QObject::connect(
       editClientSaveCommand, &Command::executed,
       commandController, &CommandController::onEditClientSaveExecuted
     );
     editClientViewContextCommands.append( editClientSaveCommand );


     Command *editClientDeleteCommand = new Command(
      commandController, QChar(  0xf235 ), "Delete"
     );
     QObject::connect(
       editClientDeleteCommand, &Command::executed,
       commandController, &CommandController::onEditClientDeleteExecuted
     );
     editClientViewContextCommands.append( editClientDeleteCommand );
  }

  CommandController *commandController{nullptr};

  QList<Command*> createClientVIewContextCommands{};
  QList<Command*> findClientViewContextCommands{};
  QList<Command*> editClientViewContextCommands{};

  IDatabaseController  *databaseController{nullptr};
  NavigationController *navigationController{nullptr};

  models::Client       *newClient{nullptr};
  models::Client       *selectedClient{nullptr};
  models::ClientSearch *clientSearch{nullptr};
};

CommandController::CommandController(
            QObject *parent
           ,IDatabaseController  *databaseController
           ,NavigationController *navigationController
           ,models::Client       *newClient
           ,models::ClientSearch *clientSearch )
   : QObject(parent)
{
  implementation.reset( new Implementation(this
                                          ,databaseController
                                          ,navigationController
                                          ,newClient
                                          ,clientSearch) );
}

CommandController::~CommandController() {}

void CommandController::setSelectedClient(models::Client *client)
{
  implementation->selectedClient = client;
}

QQmlListProperty<Command>
CommandController::ui_createClientViewContextCommands()
{
   return QQmlListProperty<Command>(
            this,
            implementation->createClientVIewContextCommands );
}

void CommandController::onCreateClientSaveExecuted()
{
  std::cout << "You executed the Save Command!" << std::endl;

  implementation->databaseController->createRow(
    implementation->newClient->key()
   ,implementation->newClient->id()
   ,implementation->newClient->toJson()
  );

  std::cout << "New Client Saved!" << std::endl;


  implementation->clientSearch->searchText()
                ->setValue( implementation->newClient->id() );
  implementation->clientSearch->search();
  implementation->navigationController->goFindClientView();
}

QQmlListProperty<Command>
CommandController::ui_findClientViewContextCommands()
{
   return QQmlListProperty<Command>(
            this,
            implementation->findClientViewContextCommands );
}

void CommandController::onFindClientViewContextCommands()
{
  std::cout << "You executed the Search Command!" << std::endl;
  implementation->clientSearch->search();
}


QQmlListProperty<Command>
CommandController::ui_editClientViewContextCommands()
{
   return QQmlListProperty<Command>(
            this,
            implementation->editClientViewContextCommands );
}

void CommandController::onEditClientSaveExecuted()
{
  std::cout << "You executed the Edit Command!" << std::endl;

  bool r = implementation->databaseController->updateRow(
    implementation->selectedClient->key()
   ,implementation->selectedClient->id()
   ,implementation->selectedClient->toJson() );

  if ( r ) {
    std::cout << "Client Updated"     << std::endl;
  } else {
    std::cout << "Client NOT Updated" << std::endl;
  }
}


QQmlListProperty<Command>
CommandController::ui_deleteClientViewContextCommands()
{
   return QQmlListProperty<Command>(
            this,
            implementation->editClientViewContextCommands );
}

void CommandController::onEditClientDeleteExecuted()
{
  std::cout << "You executed the Delete Command!" << std::endl;
  implementation->databaseController->deleteRow(
    implementation->selectedClient->key()
   ,implementation->selectedClient->id() );

  implementation->selectedClient = nullptr;

  std::cout << "Client deleted" << std::endl;

  implementation->clientSearch->search();
  implementation->navigationController->goDashboardView();
}

} // constrollers
} // lg

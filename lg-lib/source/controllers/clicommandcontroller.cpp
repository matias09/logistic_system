#include "clicommandcontroller.h"

#include <QList>

#include <iostream>

using namespace lg::framework;

namespace lg {
namespace controllers {

class CliCommandController::Implementation
{
public:
  Implementation(
            CliCommandController *_cliCommandController
           ,DatabaseController   *_databaseController
           ,NavigationController *_navigationController
           ,models::Client       *_newClient
           ,models::ClientSearch *_clientSearch )
    : cliCommandController(_cliCommandController)
    , databaseController(_databaseController)
    , navigationController(_navigationController)
    , newClient(_newClient)
    , clientSearch(_clientSearch)
  {
     Command *createClientFillCommand = new Command(
       cliCommandController, QChar( 0xf234 ), "Nuevo"
     );
     QObject::connect(
       createClientFillCommand, &Command::executed,
       cliCommandController, &CliCommandController::onCreateClientFillExecuted
     );

     Command *createClientSaveCommand = new Command(
       cliCommandController, QChar(  0xf0c7 ), "Guardar"
     );
     QObject::connect(
       createClientSaveCommand, &Command::executed,
       cliCommandController, &CliCommandController::onCreateClientSaveExecuted
     );
     createClientVIewContextCommands.append( createClientSaveCommand );

     Command *findClientSearchCommand = new Command(
      cliCommandController, QChar(  0xf002 ), "Buscar"
     );
     QObject::connect(
       findClientSearchCommand, &Command::executed,
       cliCommandController, &CliCommandController::onFindClientViewContextCommands
     );
     findClientViewContextCommands.append( findClientSearchCommand );
     findClientViewContextCommands.append( createClientFillCommand );


     Command *editClientSaveCommand = new Command(
      cliCommandController, QChar(  0xf0c7 ), "Editar"
     );
     QObject::connect(
       editClientSaveCommand, &Command::executed,
       cliCommandController, &CliCommandController::onEditClientSaveExecuted
     );
     editClientViewContextCommands.append( editClientSaveCommand );


     Command *editClientDeleteCommand = new Command(
      cliCommandController, QChar(  0xf235 ), "Borrar"
     );
     QObject::connect(
       editClientDeleteCommand, &Command::executed,
       cliCommandController, &CliCommandController::onEditClientDeleteExecuted
     );
     editClientViewContextCommands.append( editClientDeleteCommand );
  }

  CliCommandController *cliCommandController{nullptr};

  QList<Command*> createClientVIewContextCommands{};
  QList<Command*> findClientViewContextCommands{};
  QList<Command*> editClientViewContextCommands{};

  DatabaseController   *databaseController{nullptr};
  NavigationController *navigationController{nullptr};

  models::Client       *newClient{nullptr};
  models::Client       *selectedClient{nullptr};
  models::ClientSearch *clientSearch{nullptr};
};

CliCommandController::CliCommandController(
            QObject *parent
           ,DatabaseController   *databaseController
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

CliCommandController::~CliCommandController() {}

void CliCommandController::setSelectedClient(models::Client *client)
{
  implementation->selectedClient = client;
}

QQmlListProperty<Command>
CliCommandController::ui_createClientViewContextCommands()
{
   return QQmlListProperty<Command>(
            this,
            implementation->createClientVIewContextCommands );
}

void CliCommandController::onCreateClientFillExecuted()
{
  std::cout << "You executed the Create New Client Command!" << std::endl;

  implementation->navigationController->goCreateClientView();
}

void CliCommandController::onCreateClientSaveExecuted()
{
  std::cout << "You executed the Save Command!" << std::endl;

  bool r = implementation->databaseController->createClient(
    implementation->newClient->id()
   ,implementation->newClient->toJson()
  );

  if (r) {
    std::cout << "New Client Saved!" << std::endl;

    implementation->clientSearch->searchText()
                  ->setValue( implementation->newClient->name->value() );
    implementation->clientSearch->search();
    implementation->navigationController->goFindClientView();
  } else {
    implementation->navigationController->goDashboardView();
  }
}

QQmlListProperty<Command>
CliCommandController::ui_findClientViewContextCommands()
{
   return QQmlListProperty<Command>(
            this,
            implementation->findClientViewContextCommands );
}

void CliCommandController::onFindClientViewContextCommands()
{
  std::cout << "You executed the Search Command!" << std::endl;
  implementation->clientSearch->search();
}


QQmlListProperty<Command>
CliCommandController::ui_editClientViewContextCommands()
{
   return QQmlListProperty<Command>(
            this,
            implementation->editClientViewContextCommands );
}

void CliCommandController::onEditClientSaveExecuted()
{
  std::cout << "You executed the Edit Command!" << std::endl;

  bool r = implementation->databaseController->updateClient(
    implementation->selectedClient->id()
   ,implementation->selectedClient->toJson() );

  if ( r ) {
    std::cout << "Client Updated"     << std::endl;
  } else {
    std::cout << "Client NOT Updated" << std::endl;
  }
}


QQmlListProperty<Command>
CliCommandController::ui_deleteClientViewContextCommands()
{
   return QQmlListProperty<Command>(
            this,
            implementation->editClientViewContextCommands );
}

void CliCommandController::onEditClientDeleteExecuted()
{
  std::cout << "You executed the Delete Command!" << std::endl;
  implementation->databaseController->deleteClient(
    implementation->selectedClient->id() );

  implementation->selectedClient = nullptr;

  std::cout << "Client deleted" << std::endl;

  implementation->clientSearch->search();
  implementation->navigationController->goDashboardView();
}

} // constrollers
} // lg

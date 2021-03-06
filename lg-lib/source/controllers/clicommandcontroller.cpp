#include "clicommandcontroller.h"
#include "db_operations/client/deletebyid.hpp"
#include "db_operations/client/updatebyid.hpp"
#include "db_operations/client/insert.hpp"

#include <QList>

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
       cliCommandController, QChar( 0xf234 ), "New"
     );
     QObject::connect(
       createClientFillCommand, &Command::executed,
       cliCommandController, &CliCommandController::onCreateClientFillExecuted
     );

     Command *createClientSaveCommand = new Command(
       cliCommandController, QChar(  0xf0c7 ), "Save"
     );
     QObject::connect(
       createClientSaveCommand, &Command::executed,
       cliCommandController, &CliCommandController::onCreateClientSaveExecuted
     );
     createClientVIewContextCommands.append( createClientSaveCommand );

     Command *findClientSearchCommand = new Command(
      cliCommandController, QChar(  0xf002 ), "Search"
     );
     QObject::connect(
       findClientSearchCommand, &Command::executed,
       cliCommandController, &CliCommandController::onFindClientViewContextCommands
     );
     findClientViewContextCommands.append( findClientSearchCommand );
     findClientViewContextCommands.append( createClientFillCommand );


     Command *editClientSaveCommand = new Command(
      cliCommandController, QChar(  0xf0c7 ), "Edit"
     );
     QObject::connect(
       editClientSaveCommand, &Command::executed,
       cliCommandController, &CliCommandController::onEditClientSaveExecuted
     );
     editClientViewContextCommands.append( editClientSaveCommand );


     Command *editClientDeleteCommand = new Command(
      cliCommandController, QChar(  0xf235 ), "Delete"
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
  implementation->navigationController->goCreateClientView();
}

void CliCommandController::onCreateClientSaveExecuted()
{
  bool r = Insert::call(implementation->newClient->toJson()
                     ,*(implementation->databaseController) );

  if (r) {
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
  bool r = UpdateById::call( implementation->selectedClient->toJson()
                          ,  implementation->selectedClient->id()
                          ,*(implementation->databaseController) );

  if ( r ) {
    implementation->clientSearch->searchText()
                  ->setValue( implementation->selectedClient->name->value() );

    implementation->selectedClient->reset();

    implementation->clientSearch->search();
    implementation->navigationController->goFindClientView();
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
  QString err = "";
  bool r = DeleteById::call( err
                          ,  implementation->selectedClient->id()
                          ,*(implementation->databaseController) );
  if ( r ) {
    implementation->selectedClient = nullptr;

    implementation->clientSearch->search();
    implementation->navigationController->goDashboardView();
  } else {
    implementation->selectedClient->err->setValue(err);
  }
}

} // constrollers
} // lg

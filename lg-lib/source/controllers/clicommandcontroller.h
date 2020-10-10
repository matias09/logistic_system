#ifndef CLICOMMANDCONTROLLER_H
#define CLICOMMANDCONTROLLER_H

#include <QObject>
#include <QtQml/QQmlListProperty>

#include <lg-lib_global.h>
#include <framework/command.h>

#include <controllers/databasecontroller.h>
#include <controllers/navigationcontroller.h>

#include <models/client.h>
#include <models/clientsearch.h>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT  CliCommandController : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QQmlListProperty<lg::framework::Command>
    ui_createClientViewContextCommands READ
    ui_createClientViewContextCommands CONSTANT)

  Q_PROPERTY(QQmlListProperty<lg::framework::Command>
    ui_findClientViewContextCommands READ
    ui_findClientViewContextCommands CONSTANT)

  Q_PROPERTY(QQmlListProperty<lg::framework::Command>
    ui_editClientViewContextCommands READ
    ui_editClientViewContextCommands CONSTANT)

  Q_PROPERTY(QQmlListProperty<lg::framework::Command>
    ui_deleteClientViewContextCommands READ
    ui_deleteClientViewContextCommands CONSTANT)

public:
  explicit CliCommandController(
    QObject              *parent = nullptr
   ,DatabaseController   *databaseController = nullptr
   ,NavigationController *navigationController = nullptr
   ,models::Client       *newClient = nullptr
   ,models::ClientSearch *clientSearch = nullptr);

  ~CliCommandController();

  QQmlListProperty<framework::Command> ui_createClientViewContextCommands();
  QQmlListProperty<framework::Command> ui_findClientViewContextCommands();
  QQmlListProperty<framework::Command> ui_editClientViewContextCommands();
  QQmlListProperty<framework::Command> ui_deleteClientViewContextCommands();

  void setSelectedClient(models::Client *client);

public slots:
  void onCreateClientFillExecuted();
  void onCreateClientSaveExecuted();
  void onFindClientViewContextCommands();
  void onEditClientSaveExecuted();
  void onEditClientDeleteExecuted();

 private:
  class  Implementation;
  QScopedPointer<Implementation> implementation;

  class Insert;
  class UpdateById;
  class DeleteById;
};

} // controllers
} // lg

#endif // CLICOMMANDCONTROLLER_H

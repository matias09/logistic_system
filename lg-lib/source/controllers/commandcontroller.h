#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H

#include <QObject>
#include <QtQml/QQmlListProperty>

#include <lg-lib_global.h>
#include <framework/command.h>

#include <controllers/idatabasecontroller.h>
#include <controllers/navigationcontroller.h>

#include <models/client.h>
#include <models/clientsearch.h>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT  CommandController : public QObject
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
  explicit CommandController(
    QObject              *parent = nullptr
   ,IDatabaseController  *databaseController = nullptr
   ,NavigationController *navigationController = nullptr
   ,models::Client       *newClient = nullptr
   ,models::ClientSearch *clientSearch = nullptr);

  ~CommandController();

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
};

} // controllers
} // lg

#endif // COMMANDCONTROLLER_H

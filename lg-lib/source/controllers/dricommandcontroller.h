#ifndef DRICOMMANDCONTROLLER_H
#define DRICOMMANDCONTROLLER_H

#include <QObject>
#include <QtQml/QQmlListProperty>

#include <lg-lib_global.h>
#include <framework/command.h>

#include <controllers/databasecontroller.h>
#include <controllers/navigationcontroller.h>

#include <models/driver.h>
#include <models/driversearch.h>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT  DriCommandController : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QQmlListProperty<lg::framework::Command>
    ui_createDriverViewContextCommands READ
    ui_createDriverViewContextCommands CONSTANT)

  Q_PROPERTY(QQmlListProperty<lg::framework::Command>
    ui_findDriverViewContextCommands READ
    ui_findDriverViewContextCommands CONSTANT)

  Q_PROPERTY(QQmlListProperty<lg::framework::Command>
    ui_editDriverViewContextCommands READ
    ui_editDriverViewContextCommands CONSTANT)

  Q_PROPERTY(QQmlListProperty<lg::framework::Command>
    ui_deleteDriverViewContextCommands READ
    ui_deleteDriverViewContextCommands CONSTANT)

public:
  explicit DriCommandController(
    QObject              *parent = nullptr
   ,DatabaseController   *databaseController = nullptr
   ,NavigationController *navigationController = nullptr
   ,models::Driver       *newDriver = nullptr
   ,models::DriverSearch *driverSearch = nullptr);

  ~DriCommandController();

  QQmlListProperty<framework::Command> ui_createDriverViewContextCommands();
  QQmlListProperty<framework::Command> ui_findDriverViewContextCommands();
  QQmlListProperty<framework::Command> ui_editDriverViewContextCommands();
  QQmlListProperty<framework::Command> ui_deleteDriverViewContextCommands();

  void setSelectedDriver(models::Driver *driver);

public slots:
  void onCreateDriverFillExecuted();
  void onCreateDriverSaveExecuted();
  void onFindDriverViewContextCommands();
  void onEditDriverSaveExecuted();
  void onEditDriverDeleteExecuted();

 private:
  class  Implementation;
  QScopedPointer<Implementation> implementation;

  class Insert;
  class UpdateById;
  class DeleteById;
};

} // controllers
} // lg

#endif // DRICOMMANDCONTROLLER_H

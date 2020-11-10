#ifndef TRACOMMANDCONTROLLER_H
#define TRACOMMANDCONTROLLER_H

#include <QObject>
#include <QtQml/QQmlListProperty>

#include <lg-lib_global.h>
#include <framework/command.h>

#include <data/combooption.h>

#include <controllers/databasecontroller.h>
#include <controllers/navigationcontroller.h>

#include <models/travel.h>
#include <models/travelsearch.h>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT  TraCommandController : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QQmlListProperty<lg::framework::Command>
    ui_createTravelViewContextCommands READ
    ui_createTravelViewContextCommands CONSTANT)

  Q_PROPERTY(QQmlListProperty<lg::framework::Command>
    ui_findTravelViewContextCommands READ
    ui_findTravelViewContextCommands CONSTANT)

  Q_PROPERTY(QQmlListProperty<lg::framework::Command>
    ui_editTravelViewContextCommands READ
    ui_editTravelViewContextCommands CONSTANT)

  Q_PROPERTY(QQmlListProperty<lg::framework::Command>
    ui_deleteTravelViewContextCommands READ
    ui_deleteTravelViewContextCommands CONSTANT)


  Q_PROPERTY(QQmlListProperty<lg::data::ComboOption>
    ui_clients READ clients CONSTANT)
  Q_PROPERTY(QQmlListProperty<lg::data::ComboOption>
    ui_drivers READ drivers CONSTANT)
  Q_PROPERTY(QQmlListProperty<lg::data::ComboOption>
    ui_vehicles READ vehicles CONSTANT)

public:
  explicit TraCommandController(
    QObject              *parent = nullptr
   ,DatabaseController   *databaseController = nullptr
   ,NavigationController *navigationController = nullptr
   ,models::Travel       *newTravel = nullptr
   ,models::TravelSearch *travelSearch = nullptr);

  ~TraCommandController();

  QQmlListProperty<framework::Command> ui_createTravelViewContextCommands();
  QQmlListProperty<framework::Command> ui_findTravelViewContextCommands();
  QQmlListProperty<framework::Command> ui_editTravelViewContextCommands();
  QQmlListProperty<framework::Command> ui_deleteTravelViewContextCommands();

  QQmlListProperty<data::ComboOption> clients();
  QQmlListProperty<data::ComboOption> drivers();
  QQmlListProperty<data::ComboOption> vehicles();

  void setSelectedTravel(models::Travel *travel);

public slots:
  void onCreateTravelFillExecuted();
  void onCreateTravelSaveExecuted();
  void onFindTravelViewContextCommands();
  void onEditTravelSaveExecuted();
  void onEditTravelDeleteExecuted();

 private:
  class  Implementation;
  QScopedPointer<Implementation> implementation;

  class Insert;
  class UpdateById;
  class DeleteById;
};

} // controllers
} // lg

#endif // TRACOMMANDCONTROLLER_H

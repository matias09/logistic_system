#ifndef VEHCOMMANDCONTROLLER_H
#define VEHCOMMANDCONTROLLER_H

#include <QObject>
#include <QtQml/QQmlListProperty>

#include <lg-lib_global.h>
#include <framework/command.h>

#include <controllers/databasecontroller.h>
#include <controllers/navigationcontroller.h>

#include <data/combooption.h>

#include <models/vehicle.h>
#include <models/vehiclesearch.h>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT  VehCommandController : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QQmlListProperty<lg::framework::Command>
    ui_createVehicleViewContextCommands READ
    ui_createVehicleViewContextCommands CONSTANT)

  Q_PROPERTY(QQmlListProperty<lg::framework::Command>
    ui_findVehicleViewContextCommands READ
    ui_findVehicleViewContextCommands CONSTANT)

  Q_PROPERTY(QQmlListProperty<lg::framework::Command>
    ui_editVehicleViewContextCommands READ
    ui_editVehicleViewContextCommands CONSTANT)

  Q_PROPERTY(QQmlListProperty<lg::framework::Command>
    ui_deleteVehicleViewContextCommands READ
    ui_deleteVehicleViewContextCommands CONSTANT)


  Q_PROPERTY(QQmlListProperty<lg::data::ComboOption>
    ui_types READ types)

  Q_PROPERTY(QQmlListProperty<lg::data::ComboOption>
    ui_brands READ brands )

  Q_PROPERTY(QQmlListProperty<lg::data::ComboOption>
    ui_models READ models)

public:
  explicit VehCommandController(
    QObject              *parent = nullptr
   ,DatabaseController   *databaseController = nullptr
   ,NavigationController *navigationController = nullptr
   ,models::Vehicle       *newVehicle = nullptr
   ,models::VehicleSearch *vehicleSearch = nullptr);

  ~VehCommandController();

  QQmlListProperty<framework::Command> ui_createVehicleViewContextCommands();
  QQmlListProperty<framework::Command> ui_findVehicleViewContextCommands();
  QQmlListProperty<framework::Command> ui_editVehicleViewContextCommands();
  QQmlListProperty<framework::Command> ui_deleteVehicleViewContextCommands();

  QQmlListProperty<data::ComboOption> types();
  QQmlListProperty<data::ComboOption> brands();
  QQmlListProperty<data::ComboOption> models();

  void setSelectedVehicle(models::Vehicle *vehicle);


public slots:
  void onCreateVehicleFillExecuted();
  void onCreateVehicleSaveExecuted();
  void onFindVehicleViewContextCommands();
  void onEditVehicleSaveExecuted();
  void onEditVehicleDeleteExecuted();
  void onBrandsChanged(const int bid);

 private:
  class  Implementation;
  QScopedPointer<Implementation> implementation;

  class Insert;
  class UpdateById;
  class DeleteById;
  class GetOptModelByBrandId;
};

} // controllers
} // lg

#endif // VEHCOMMANDCONTROLLER_H

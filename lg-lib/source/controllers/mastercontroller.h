#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QObject>
#include <QScopedPointer>
#include <QString>

#include <lg-lib_global.h>

#include <controllers/navigationcontroller.h>
#include <controllers/clicommandcontroller.h>
#include <controllers/dricommandcontroller.h>
#include <controllers/vehcommandcontroller.h>
#include <controllers/tracommandcontroller.h>
#include <controllers/databasecontroller.h>

#include <models/client.h>
#include <models/clientsearch.h>
#include <models/driver.h>
#include <models/driversearch.h>
#include <models/travel.h>
#include <models/travelsearch.h>
#include <models/vehicle.h>
#include <models/vehiclesearch.h>

#include <models/combooption.h>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT MasterController : public QObject
{
  Q_OBJECT

  Q_PROPERTY(lg::controllers::NavigationController *ui_navigationController
    READ  navigationController CONSTANT)
  Q_PROPERTY(lg::controllers::CliCommandController *ui_cliCommandController
    READ  cliCommandController CONSTANT)
  Q_PROPERTY(lg::controllers::DriCommandController *ui_driCommandController
    READ  driCommandController CONSTANT)
  Q_PROPERTY(lg::controllers::VehCommandController *ui_vehCommandController
    READ  vehCommandController CONSTANT)
  Q_PROPERTY(lg::controllers::TraCommandController *ui_traCommandController
    READ  traCommandController CONSTANT)

  Q_PROPERTY(lg::models::Client *ui_newClient
    READ  newClient CONSTANT)
  Q_PROPERTY(lg::models::ClientSearch *ui_clientSearch
    READ  clientSearch CONSTANT)

  Q_PROPERTY(lg::models::Driver *ui_newDriver
    READ  newDriver CONSTANT)
  Q_PROPERTY(lg::models::DriverSearch *ui_driverSearch
    READ  driverSearch CONSTANT)

  Q_PROPERTY(lg::models::Vehicle *ui_newVehicle
    READ  newVehicle CONSTANT)
  Q_PROPERTY(lg::models::VehicleSearch *ui_vehicleSearch
    READ  vehicleSearch CONSTANT)

  Q_PROPERTY(lg::models::Travel *ui_newTravel
    READ  newTravel CONSTANT)
  Q_PROPERTY(lg::models::TravelSearch *ui_travelSearch
    READ  travelSearch CONSTANT)

  Q_PROPERTY(QQmlListProperty<lg::models::ComboOption>
      ui_countries READ countries)

public:
  explicit MasterController(QObject *parent = nullptr);
  ~MasterController();

  NavigationController* navigationController();
  CliCommandController* cliCommandController();
  DriCommandController* driCommandController();
  VehCommandController* vehCommandController();
  TraCommandController* traCommandController();
  DatabaseController*   databaseController();

  models::Client*       newClient();
  models::ClientSearch* clientSearch();

  models::Driver*       newDriver();
  models::DriverSearch* driverSearch();

  models::Vehicle*       newVehicle();
  models::VehicleSearch* vehicleSearch();

  models::Travel*       newTravel();
  models::TravelSearch* travelSearch();

  QQmlListProperty<models::ComboOption> countries();

public slots:
  void selectClient( lg::models::Client *client );
  void selectDriver( lg::models::Driver *driver );
  void selectVehicle( lg::models::Vehicle *vehicle );
  void selectTravel( lg::models::Travel *travel );

private:
  class Implementation;
  QScopedPointer<Implementation> implementation;

  class GetAllCountries;
};

} // controllers
} // lg
#endif // MASTERCONTROLLER_H

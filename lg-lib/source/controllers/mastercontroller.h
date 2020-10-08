#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QObject>
#include <QScopedPointer>
#include <QString>

#include <lg-lib_global.h>

#include <controllers/navigationcontroller.h>
#include <controllers/clicommandcontroller.h>
#include <controllers/dricommandcontroller.h>
#include <controllers/databasecontroller.h>

#include <models/client.h>
#include <models/clientsearch.h>
#include <models/driver.h>
#include <models/driversearch.h>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT MasterController : public QObject
{
  Q_OBJECT

  Q_PROPERTY(lg::controllers::NavigationController* ui_navigationController
    READ  navigationController CONSTANT)
  Q_PROPERTY(lg::controllers::CliCommandController* ui_cliCommandController
    READ  cliCommandController CONSTANT)
  Q_PROPERTY(lg::controllers::DriCommandController* ui_driCommandController
    READ  driCommandController CONSTANT)

  Q_PROPERTY(lg::models::Client* ui_newClient
    READ  newClient CONSTANT)
  Q_PROPERTY(lg::models::ClientSearch* ui_clientSearch
    READ  clientSearch CONSTANT)

  Q_PROPERTY(lg::models::Driver* ui_newDriver
    READ  newDriver CONSTANT)
  Q_PROPERTY(lg::models::DriverSearch* ui_driverSearch
    READ  driverSearch CONSTANT)

public:
  explicit MasterController(QObject *parent = nullptr);
  ~MasterController();

  NavigationController* navigationController();
  CliCommandController* cliCommandController();
  DriCommandController* driCommandController();
  DatabaseController*   databaseController();

  models::Client*       newClient();
  models::ClientSearch* clientSearch();

  models::Driver*       newDriver();
  models::DriverSearch* driverSearch();

public slots:
  void selectClient( lg::models::Client *client );
  void selectDriver( lg::models::Driver *driver );

private:
  class Implementation;
  QScopedPointer<Implementation> implementation;
};

} // controllers
} // lg
#endif // MASTERCONTROLLER_H

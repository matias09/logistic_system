#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QObject>
#include <QScopedPointer>
#include <QString>

#include <lg-lib_global.h>

#include <controllers/navigationcontroller.h>
#include <controllers/clicommandcontroller.h>
#include <controllers/databasecontroller.h>

#include <models/client.h>
#include <models/clientsearch.h>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT MasterController : public QObject
{
  Q_OBJECT

  Q_PROPERTY(lg::controllers::NavigationController* ui_navigationController
    READ  navigationController CONSTANT)
  Q_PROPERTY(lg::controllers::CliCommandController* ui_cliCommandController
    READ  cliCommandController CONSTANT)

  Q_PROPERTY(lg::models::Client* ui_newClient
    READ  newClient CONSTANT)
  Q_PROPERTY(lg::models::ClientSearch* ui_clientSearch
    READ  clientSearch CONSTANT)

public:
  explicit MasterController(QObject *parent = nullptr);
  ~MasterController();

  NavigationController* navigationController();
  CliCommandController* cliCommandController();
  DatabaseController*   databaseController();

  models::Client*       newClient();
  models::ClientSearch* clientSearch();

public slots:
  void selectClient( lg::models::Client *client );

private:
  class Implementation;
  QScopedPointer<Implementation> implementation;
};

} // controllers
} // lg
#endif // MASTERCONTROLLER_H

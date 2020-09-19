#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QObject>
#include <QScopedPointer>
#include <QString>

#include <lg-lib_global.h>

#include <controllers/navigationcontroller.h>
#include <controllers/commandcontroller.h>
#include <controllers/databasecontroller.h>

#include <models/client.h>
#include <models/clientsearch.h>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT MasterController : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString  ui_welcomeMessage READ welcomeMessage CONSTANT)

  Q_PROPERTY(lg::controllers::NavigationController* ui_navigationController
    READ  navigationController CONSTANT)
  Q_PROPERTY(lg::controllers::CommandController* ui_commandController
    READ  commandController CONSTANT)
  Q_PROPERTY(lg::controllers::DatabaseController* ui_databaseController
    READ  databaseController CONSTANT)

  Q_PROPERTY(lg::models::Client* ui_newClient
    READ  newClient CONSTANT)
  Q_PROPERTY(lg::models::ClientSearch* ui_clientSearch
    READ  clientSearch CONSTANT)

public:
  explicit MasterController(QObject *parent = nullptr);
  ~MasterController();

  NavigationController* navigationController();
  CommandController* commandController();
  DatabaseController* databaseController();
  const QString& welcomeMessage() const;

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

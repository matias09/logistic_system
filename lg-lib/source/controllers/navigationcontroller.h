#ifndef NAVIGATIONCONTROLLER_H
#define NAVIGATIONCONTROLLER_H

#include <QObject>

#include <lg-lib_global.h>

#include <models/client.h>
#include <models/driver.h>
#include <models/vehicle.h>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT NavigationController : public QObject
{
  Q_OBJECT
public:
  explicit NavigationController(QObject* _parent = nullptr)
    : QObject(_parent)
    {}

signals:
  void goDashboardView();

  void goCreateClientView();
  void goEditClientView(lg::models::Client *client);
  void goFindClientView();

  void goCreateDriverView();
  void goEditDriverView(lg::models::Driver *driver);
  void goFindDriverView();

  void goCreateVehicleView();
  void goEditVehicleView(lg::models::Vehicle *vehicle);
  void goFindVehicleView();
};

} // controllers
} // lg

#endif // NAVIGATIONCONTROLLER_H

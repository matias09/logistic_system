#ifndef NAVIGATIONCONTROLLER_H
#define NAVIGATIONCONTROLLER_H

#include <QObject>

#include <lg-lib_global.h>
#include <models/client.h>

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
  void goEditClientView(lg::models::Client* client);
  void goFindClientView();
};

} // controllers
} // lg

#endif // NAVIGATIONCONTROLLER_H

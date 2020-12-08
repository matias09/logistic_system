#ifndef DRIVER_H
#define DRIVER_H

#include <QObject>
#include <QtQml/QQmlListProperty>

#include <lg-lib_global.h>

#include <data/stringdecorator.h>
#include <data/entity.h>
#include <data/entitycollection.h>

#include <models/address.h>

namespace lg {
namespace models {

class LGLIBSHARED_EXPORT Driver : public data::Entity
{
  Q_OBJECT
  Q_PROPERTY(lg::data::StringDecorator* ui_reference MEMBER reference CONSTANT)
  Q_PROPERTY(lg::data::StringDecorator* ui_name      MEMBER name      CONSTANT)

  Q_PROPERTY(lg::data::StringDecorator* ui_lic_nro   MEMBER lic_nro   CONSTANT)
  Q_PROPERTY(lg::data::StringDecorator* ui_lic_cad   MEMBER lic_cad   CONSTANT)

  Q_PROPERTY(lg::data::StringDecorator* ui_phone     MEMBER phone     CONSTANT)
  Q_PROPERTY(lg::data::StringDecorator* ui_cellphone MEMBER cellphone CONSTANT)
  Q_PROPERTY(lg::data::StringDecorator* ui_mail      MEMBER mail      CONSTANT)

  Q_PROPERTY(lg::data::StringDecorator* ui_err      MEMBER err      CONSTANT)

  Q_PROPERTY(lg::models::Address* ui_driverAddress MEMBER address CONSTANT)

public:
  explicit Driver(QObject *parent = nullptr);
  Driver(QObject *parent, const QJsonObject &json);

  void reset();

  data::StringDecorator *reference{nullptr};
  data::StringDecorator *name{nullptr};
  data::StringDecorator *lic_nro{nullptr};
  data::StringDecorator *lic_cad{nullptr};
  data::StringDecorator *phone{nullptr};
  data::StringDecorator *cellphone{nullptr};
  data::StringDecorator *mail{nullptr};
  data::StringDecorator *err{nullptr};

  Address *address{nullptr};

signals:
  void appointmentsChanged();
  void contactsChanged();
};

} // models
} // lg
#endif // DRIVER_H

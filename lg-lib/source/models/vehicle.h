#ifndef VEHICLE_H
#define VEHICLE_H

#include <QObject>
#include <QtQml/QQmlListProperty>

#include <lg-lib_global.h>

#include <data/stringdecorator.h>
#include <data/entity.h>
#include <data/entitycollection.h>

namespace lg {
namespace models {

class LGLIBSHARED_EXPORT Vehicle : public data::Entity
{
  Q_OBJECT
  Q_PROPERTY(lg::data::StringDecorator* ui_reference MEMBER reference CONSTANT)
  Q_PROPERTY(lg::data::StringDecorator* ui_type      MEMBER type      CONSTANT)
  Q_PROPERTY(lg::data::StringDecorator* ui_brand     MEMBER brand     CONSTANT)
  Q_PROPERTY(lg::data::StringDecorator* ui_model     MEMBER model     CONSTANT)
  Q_PROPERTY(lg::data::StringDecorator* ui_max_w     MEMBER max_w     CONSTANT)
  Q_PROPERTY(lg::data::StringDecorator* ui_vin       MEMBER vin       CONSTANT)
  Q_PROPERTY(lg::data::StringDecorator* ui_vin_cad   MEMBER vin_cad   CONSTANT)
  Q_PROPERTY(lg::data::StringDecorator* ui_year      MEMBER year      CONSTANT)

public:
  explicit Vehicle(QObject *parent = nullptr);
  Vehicle(QObject *parent, const QJsonObject &json);

  data::StringDecorator *reference {nullptr};
  data::StringDecorator *type      {nullptr};
  data::StringDecorator *brand     {nullptr};
  data::StringDecorator *model     {nullptr};
  data::StringDecorator *max_w     {nullptr};
  data::StringDecorator *vin       {nullptr};
  data::StringDecorator *vin_cad   {nullptr};
  data::StringDecorator *year      {nullptr};

signals:
};

} // models
} // lg
#endif // VEHICLE_H

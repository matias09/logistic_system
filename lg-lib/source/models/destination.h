#ifndef DESTINATION_H
#define DESTINATION_H

#include <QObject>

#include <lg-lib_global.h>

#include <data/stringdecorator.h>
#include <data/entity.h>
#include <data/entitycollection.h>

#include <models/address.h>

namespace lg {
namespace models {

class LGLIBSHARED_EXPORT Destination : public data::Entity
{
  Q_OBJECT
  Q_PROPERTY(lg::data::StringDecorator* ui_reference MEMBER reference CONSTANT)

  Q_PROPERTY(lg::data::StringDecorator* ui_id_dri MEMBER id_dri  CONSTANT)
  Q_PROPERTY(lg::data::StringDecorator* ui_id_veh MEMBER id_veh  CONSTANT)

  Q_PROPERTY(lg::data::StringDecorator* ui_arr_date MEMBER arr_date   CONSTANT)

  Q_PROPERTY(lg::models::Address* ui_address MEMBER address CONSTANT)

public:
  explicit Destination(QObject *parent = nullptr);
  Destination(QObject *parent, const QJsonObject &json);

  data::StringDecorator *reference{nullptr};
  data::StringDecorator *id_dri{nullptr};
  data::StringDecorator *id_veh{nullptr};
  data::StringDecorator *arr_date{nullptr};

  Address *address{nullptr};

signals:
};

} // models
} // lg
#endif // DESTINATION_H

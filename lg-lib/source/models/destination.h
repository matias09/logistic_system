#ifndef DESTINATION_H
#define DESTINATION_H

#include <QObject>

#include <lg-lib_global.h>

#include <data/entity.h>
#include <data/entitycollection.h>
#include <data/datetimedecorator.h>

#include <models/address.h>

namespace lg {
namespace models {

class LGLIBSHARED_EXPORT Destination : public data::Entity
{
  Q_OBJECT
  Q_PROPERTY(lg::data::StringDecorator* ui_reference MEMBER reference CONSTANT)

  Q_PROPERTY(lg::data::IntDecorator* ui_id_dri   MEMBER id_dri    CONSTANT)
  Q_PROPERTY(lg::data::IntDecorator* ui_id_veh   MEMBER id_veh    CONSTANT)
  Q_PROPERTY(lg::data::IntDecorator* ui_id_dri_o MEMBER id_dri_o  CONSTANT)
  Q_PROPERTY(lg::data::IntDecorator* ui_id_veh_o MEMBER id_veh_o  CONSTANT)

  Q_PROPERTY(lg::data::StringDecorator* ui_dri    MEMBER dri     CONSTANT)
  Q_PROPERTY(lg::data::StringDecorator* ui_veh    MEMBER veh     CONSTANT)

  Q_PROPERTY(lg::data::DateTimeDecorator* ui_arr_date MEMBER arr_date CONSTANT)

  Q_PROPERTY(lg::models::Address* ui_address MEMBER address CONSTANT)

  Q_PROPERTY(lg::data::StringDecorator* ui_err MEMBER err CONSTANT)

public:
  explicit Destination(QObject *parent = nullptr);
  Destination(QObject *parent, const QJsonObject &json);

  void reset();

  data::IntDecorator *id_dri  {nullptr};
  data::IntDecorator *id_veh  {nullptr};
  data::IntDecorator *id_dri_o{nullptr};
  data::IntDecorator *id_veh_o{nullptr};

  data::StringDecorator *reference{nullptr};
  data::StringDecorator *dri{nullptr};
  data::StringDecorator *veh{nullptr};

  data::DateTimeDecorator *arr_date{nullptr};

  data::StringDecorator *err{nullptr};

  Address *address{nullptr};

signals:
};

} // models
} // lg
#endif // DESTINATION_H

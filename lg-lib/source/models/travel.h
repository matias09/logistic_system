#ifndef TRAVEL_H
#define TRAVEL_H

#include <QObject>

#include <lg-lib_global.h>

#include <data/entity.h>
#include <data/entitycollection.h>

#include <models/destination.h>

namespace lg {
namespace models {

class LGLIBSHARED_EXPORT Travel : public data::Entity
{
  Q_OBJECT
  Q_PROPERTY(lg::data::StringDecorator* ui_reference MEMBER reference CONSTANT)

  Q_PROPERTY(lg::data::IntDecorator* ui_canceled     MEMBER canceled CONSTANT)
  Q_PROPERTY(lg::data::IntDecorator* ui_ended        MEMBER ended    CONSTANT)
  Q_PROPERTY(lg::data::IntDecorator* ui_id_cli       MEMBER id_cli   CONSTANT)

  Q_PROPERTY(lg::data::StringDecorator* ui_cli       MEMBER cli       CONSTANT)

  Q_PROPERTY(lg::data::StringDecorator* ui_sta_date MEMBER sta_date CONSTANT)

  Q_PROPERTY(lg::models::Destination* ui_destiny     MEMBER destiny   CONSTANT)

public:
  explicit Travel(QObject *parent = nullptr);
  Travel(QObject *parent, const QJsonObject &json);

  void reset();

  data::IntDecorator *canceled{nullptr};
  data::IntDecorator *ended{nullptr};
  data::IntDecorator *id_cli{nullptr};

  data::StringDecorator *reference{nullptr};
  data::StringDecorator *cli      {nullptr};

  data::StringDecorator *sta_date {nullptr};

  Destination *destiny{nullptr};

signals:
};

} // models
} // lg
#endif // TRAVEL_H

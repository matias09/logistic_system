#ifndef TRAVEL_H
#define TRAVEL_H

#include <QObject>

#include <lg-lib_global.h>

#include <data/stringdecorator.h>
#include <data/entity.h>
#include <data/entitycollection.h>

#include <models/destination.h>

namespace lg {
namespace models {

class LGLIBSHARED_EXPORT Travel : public data::Entity
{
  Q_OBJECT
  Q_PROPERTY(lg::data::StringDecorator* ui_reference MEMBER reference CONSTANT)

  Q_PROPERTY(lg::data::StringDecorator* ui_id_cli    MEMBER id_cli    CONSTANT)
  Q_PROPERTY(lg::data::StringDecorator* ui_sta_date  MEMBER sta_date  CONSTANT)

  Q_PROPERTY(lg::models::Destination* ui_destiny     MEMBER destiny   CONSTANT)

public:
  explicit Travel(QObject *parent = nullptr);
  Travel(QObject *parent, const QJsonObject &json);

  data::StringDecorator *reference{nullptr};
  data::StringDecorator *id_cli{nullptr};
  data::StringDecorator *sta_date{nullptr};

  Destination *destiny{nullptr};

signals:
};

} // models
} // lg
#endif // TRAVEL_H

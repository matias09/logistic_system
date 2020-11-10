#ifndef ADDRESS_H
#define ADDRESS_H

#include <QObject>

#include <lg-lib_global.h>
#include <data/entity.h>
#include <data/intdecorator.h>

namespace lg {
namespace models {

class LGLIBSHARED_EXPORT Address : public data::Entity
{
  Q_OBJECT
  Q_PROPERTY(lg::data::IntDecorator* ui_id_state MEMBER id_state CONSTANT)
  Q_PROPERTY(lg::data::StringDecorator* ui_state MEMBER state CONSTANT)
  Q_PROPERTY(lg::data::StringDecorator* ui_street MEMBER street CONSTANT)
  Q_PROPERTY(lg::data::StringDecorator* ui_house_nro MEMBER house_nro CONSTANT)
  Q_PROPERTY(lg::data::StringDecorator* ui_postcode MEMBER postcode CONSTANT)

  Q_PROPERTY(QString ui_fullAddress READ fullAddress CONSTANT)

public:
  explicit Address(QObject *parent = nullptr);
  Address(QObject *parent, const QJsonObject &json);

  data::IntDecorator*    id_state{nullptr};
  data::StringDecorator* state{nullptr};
  data::StringDecorator* street{nullptr};
  data::StringDecorator* house_nro{nullptr};
  data::StringDecorator* postcode{nullptr};

  QString fullAddress() const;
};

}
}
#endif // ADDRESS_H

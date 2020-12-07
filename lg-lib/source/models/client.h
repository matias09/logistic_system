#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtQml/QQmlListProperty>
#include <QString>

#include <lg-lib_global.h>

#include <data/stringdecorator.h>
#include <data/entity.h>
#include <data/entitycollection.h>

#include <models/address.h>

namespace lg {
namespace models {

class LGLIBSHARED_EXPORT Client : public data::Entity
{
  Q_OBJECT
  Q_PROPERTY(lg::data::StringDecorator* ui_reference MEMBER reference CONSTANT)
  Q_PROPERTY(lg::data::StringDecorator* ui_name      MEMBER name      CONSTANT)
  Q_PROPERTY(lg::data::StringDecorator* ui_phone     MEMBER phone     CONSTANT)
  Q_PROPERTY(lg::data::StringDecorator* ui_cellphone MEMBER cellphone CONSTANT)
  Q_PROPERTY(lg::data::StringDecorator* ui_mail      MEMBER mail      CONSTANT)

  Q_PROPERTY(lg::models::Address* ui_clientAddress MEMBER clientAddress CONSTANT)

  Q_PROPERTY(lg::data::StringDecorator* ui_err  MEMBER err  CONSTANT)

public:
  explicit Client(QObject *parent = nullptr);
  Client(QObject *parent, const QJsonObject &json);

  data::StringDecorator *reference{nullptr};
  data::StringDecorator *name{nullptr};
  data::StringDecorator *phone{nullptr};
  data::StringDecorator *cellphone{nullptr};
  data::StringDecorator *mail{nullptr};

  Address *clientAddress{nullptr};

  data::StringDecorator *err{nullptr};

  void reset();

signals:
  void appointmentsChanged();
  void contactsChanged();
};

} // models
} // lg
#endif // CLIENT_H

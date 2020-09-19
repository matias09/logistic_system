#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtQml/QQmlListProperty>

#include <lg-lib_global.h>

#include <data/stringdecorator.h>
#include <data/entity.h>
#include <data/entitycollection.h>

#include <models/address.h>
#include <models/appointment.h>
#include <models/contact.h>

namespace lg {
namespace models {

class LGLIBSHARED_EXPORT Client : public data::Entity
{
  Q_OBJECT
  Q_PROPERTY(lg::data::StringDecorator* ui_reference MEMBER reference CONSTANT)
  Q_PROPERTY(lg::data::StringDecorator* ui_name MEMBER name CONSTANT)

  Q_PROPERTY(lg::models::Address* ui_supplyAddress MEMBER supplyAddress CONSTANT)
  Q_PROPERTY(lg::models::Address* ui_billingAddress MEMBER billingAddress CONSTANT)

  Q_PROPERTY(QQmlListProperty<Appointment> ui_appointments READ ui_appointments NOTIFY appointmentsChanged)
  Q_PROPERTY(QQmlListProperty<Contact> ui_contacts READ ui_contacts NOTIFY contactsChanged)

public:
  explicit Client(QObject *parent = nullptr);
  Client(QObject *parent, const QJsonObject &json);

  data::StringDecorator *reference{nullptr};
  data::StringDecorator *name{nullptr};

  Address *supplyAddress{nullptr};
  Address *billingAddress{nullptr};

  data::EntityCollection<Appointment> *appointments{nullptr};
  data::EntityCollection<Contact> *contacts{nullptr};

  QQmlListProperty<lg::models::Appointment> ui_appointments();
  QQmlListProperty<lg::models::Contact > ui_contacts();

signals:
  void appointmentsChanged();
  void contactsChanged();
};

} // models
} // lg
#endif // CLIENT_H

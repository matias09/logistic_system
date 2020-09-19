#include "appointment.h"

using namespace lg::data;

namespace lg {
namespace models {

Appointment::Appointment(QObject *parent)
  : Entity (parent, "appointment")
{
  startAt = static_cast<DateTimeDecorator*>(addDataItem(
      new DateTimeDecorator(this, "startAt", "Starts At")
  ) );

  endAt = static_cast<DateTimeDecorator*>(addDataItem(
      new DateTimeDecorator(this, "endAt", "Ends At")
  ) );

  notes = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "notes", "Notes")
  ) );
}
Appointment::Appointment(QObject *parent, const QJsonObject &json)
  : Appointment(parent)
{
  update(json);
}

} //  models
} //  lg

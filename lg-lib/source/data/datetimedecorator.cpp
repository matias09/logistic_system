#include "datetimedecorator.h"

#include <QVariant>

namespace lg {
namespace data {

class DateTimeDecorator::Implementation
{
public:
  Implementation(
                DateTimeDecorator *_dateTimeDecorator
               ,const QDateTime &_value)
   : dateTimeDecorator(_dateTimeDecorator)
    ,value(_value) {}

    DateTimeDecorator* dateTimeDecorator{nullptr};
    QDateTime value;
};

DateTimeDecorator::DateTimeDecorator(
             Entity* parentEntity
           , const QString &key
           , const QString &label
           , const QDateTime &value )
  : DataDecorator (parentEntity, key, label)
 {
    implementation.reset( new Implementation(this, value) );
 }

DateTimeDecorator::~DateTimeDecorator() {}

 const QDateTime& DateTimeDecorator::value() const
{
    return implementation->value;
}

DateTimeDecorator& DateTimeDecorator::setValue(const QDateTime &value)
{
   if (value != implementation->value) {
    // .... validation here if required ...
      implementation->value = value;
      emit valueChanged();
   }

   return *this;
}

QJsonValue DateTimeDecorator::jsonValue() const
{
  return QJsonValue::fromVariant( QVariant(implementation->value) );
}

void DateTimeDecorator::update(const QJsonObject &_jsonObject)
{
  if (_jsonObject.contains( key() ) ) {
    QString dt = _jsonObject.value( key() ).toString();
    setValue( QDateTime::fromString(dt) );
  } else {
    setValue(QDateTime::currentDateTime());
  }
}

 QString DateTimeDecorator::toIso8601String() const
 {
    if ( implementation->value.isNull() ) {
      return "";
    } else {
      return implementation->value.toString(Qt::ISODate);
    }
 }

 QString DateTimeDecorator::toPrettyString() const
 {
    if ( implementation->value.isNull() ) {
      return "Not Set";
    } else {
      return implementation->value.toString( "ddd d MMM yyyy @ HH:mm:ss" );
    }
 }

 QString DateTimeDecorator::toPrettyDateString() const
 {
    if ( implementation->value.isNull() ) {
      return "Not Set";
    } else {
      return implementation->value.toString( "d MMM yyyy" );
    }
 }

 QString DateTimeDecorator::toPrettyTimeString() const
 {
    if ( implementation->value.isNull() ) {
      return "Not Set";
    } else {
      return implementation->value.toString( "hh:mm ap" );
    }
 }

} // data
} // lg

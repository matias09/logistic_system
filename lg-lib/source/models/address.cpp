#include "address.h"

using namespace lg::data;

namespace lg {
namespace models {

Address::Address(QObject *parent)
  : Entity (parent, "address")
{
  street  = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "street", "Calle")
  ) );

  city = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "city", "Ciudad")
  ) );

  postcode = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "postcode", "Codigo Postal")
  ) );
}
Address::Address(QObject *parent, const QJsonObject &json)
  : Address(parent)
{
  update(json);
}

QString Address::fullAddress() const
{
  return  street->value() + "\n"
          + city->value() + "\n"
          + postcode->value();
}

} //  models
} //  lg

#include "address.h"

using namespace lg::data;

namespace lg {
namespace models {

Address::Address(QObject *parent)
  : Entity (parent, "address")
{
  id_state = static_cast<IntDecorator*>(addDataItem(
      new IntDecorator(this, "id_state", "State")
  ) );

  state  = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "state", "State")
  ) );

  street  = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "street", "Street")
  ) );

  house_nro = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "house_nro", "House Number")
  ) );

  postcode = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "postcode", "Postal Code")
  ) );
}
Address::Address(QObject *parent, const QJsonObject &json)
  : Address(parent)
{
  update(json);
}

QString Address::fullAddress() const
{
  return  street->value() + " " + house_nro->value() + " " + postcode->value();
}

void Address::reset()
{
  id_state->setValue(0);

  state->setValue("");
  street->setValue("");
  house_nro->setValue("");
  postcode->setValue("");
}

} //  models
} //  lg

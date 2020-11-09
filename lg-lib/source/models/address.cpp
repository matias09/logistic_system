#include "address.h"

using namespace lg::data;

namespace lg {
namespace models {

Address::Address(QObject *parent)
  : Entity (parent, "address")
{
  id_state = static_cast<IntDecorator*>(addDataItem(
      new IntDecorator(this, "id_state", "Provincia")
  ) );

  state  = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "state", "Provincia")
  ) );

  street  = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "street", "Calle")
  ) );

  house_nro = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "house_nro", "Numeracion")
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
  return  street->value() + " "
          + house_nro->value() + "\n"
          + postcode->value();
}

} //  models
} //  lg

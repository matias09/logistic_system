#include "destination.h"

using namespace lg::data;

namespace lg {
namespace models {

Destination::Destination(QObject *parent)
  : Entity(parent, "destinations")
{
  reference = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "reference", "Referencia del Destino")
  ) );

  id_dri = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "id_dri", "Referencia del Chofer")
  ) );

  id_veh = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "id_veh", "Referencia del Vehiculo")
  ) );

  arr_date = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "arr_date", "Fecha de Entrega")
  ) );

  address = static_cast<Address*>(addChild(new Address(this), "address")  );

  setPrimaryKey(reference);
}

Destination::Destination(QObject *parent, const QJsonObject &json)
  : Destination(parent)
{
  update(json);
}

}
}

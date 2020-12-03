#include "destination.h"

#include <QDateTime>

using namespace lg::data;

namespace lg {
namespace models {

Destination::Destination(QObject *parent)
  : Entity(parent, "destinations")
{
  reference = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "reference", "Referencia del Destino") ));

  id_dri = static_cast<IntDecorator*>(addDataItem(
      new IntDecorator(this, "id_dri", "Ref. Chofer") ));

  id_veh = static_cast<IntDecorator*>(addDataItem(
      new IntDecorator(this, "id_veh", "Ref. Vehiculo") ));

  id_dri_o = static_cast<IntDecorator*>(addDataItem(
      new IntDecorator(this, "id_dri_o", "") ));

  id_veh_o = static_cast<IntDecorator*>(addDataItem(
      new IntDecorator(this, "id_veh_o", "") ));

  dri = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "dri", "Chofer") ));

  veh = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "veh", "Vehiculo") ));

  arr_date = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "arr_date", "Fecha de Entrega") ));
  arr_date->setValue(QDateTime::currentDateTime().toString());

  address = static_cast<Address*>( addChild(new Address(this), "address") );

  err = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "err", "")
  ) );

  setPrimaryKey(reference);
}

Destination::Destination(QObject *parent, const QJsonObject &json)
  : Destination(parent)
{
  update(json);
}

void Destination::reset()
{
  id_dri->setValue(0);
  id_dri_o->setValue(0);
  id_veh->setValue(0);
  id_veh_o->setValue(0);

  dri->setValue("");
  veh->setValue("");

  arr_date->setValue(QDateTime::currentDateTime().toString());

  address->reset();
}

}
}

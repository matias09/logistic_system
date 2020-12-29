#include "destination.h"

#include <QDateTime>

using namespace lg::data;

namespace lg {
namespace models {

Destination::Destination(QObject *parent)
  : Entity(parent, "destinations")
{
  reference = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "reference", "Destination ID") ));

  id_dri = static_cast<IntDecorator*>(addDataItem(
      new IntDecorator(this, "id_dri", "Driver") ));

  id_veh = static_cast<IntDecorator*>(addDataItem(
      new IntDecorator(this, "id_veh", "Vehicle") ));

  id_dri_o = static_cast<IntDecorator*>(addDataItem(
      new IntDecorator(this, "id_dri_o", "") ));

  id_veh_o = static_cast<IntDecorator*>(addDataItem(
      new IntDecorator(this, "id_veh_o", "") ));

  dri = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "dri", "Driver") ));

  veh = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "veh", "Vehicle") ));

  arr_date = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "arr_date", "Deliver Date") ));

  address = static_cast<Address*>( addChild(new Address(this), "address") );

  err = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "err", "")
  ) );

  setPrimaryKey(reference);

  reset();
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
  err->setValue("");

  arr_date->setValue(QDateTime::currentDateTime().toString(Qt::ISODate));

  address->reset();
}

}
}

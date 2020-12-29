#include "vehicle.h"

using namespace lg::data;

namespace lg {
namespace models {

Vehicle::Vehicle(QObject *parent)
  : Entity(parent, "vehicles")
{
  reference = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "reference", "Vehicle ID") ));

  id_type = static_cast<IntDecorator*>(addDataItem(
      new IntDecorator(this, "id_type", "Type") ));

  id_brand = static_cast<IntDecorator*>(addDataItem(
      new IntDecorator(this, "id_brand", "Brand") ));

  id_model = static_cast<IntDecorator*>(addDataItem(
      new IntDecorator(this, "id_model", "Model") ));

  max_w = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "max_w", "Max Weight Capacity Kg") ));

  vin = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "vin", "VIN") ));

  vin_cad = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "vin_cad", "VIN Caducity") ));

  year = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "year", "Year") ));

  type  = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "type", "Type") ));

  brand = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "brand", "Brand") ));

  model = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "model", "Model") ));

  name = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "name", "Name") ));

  err = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "err", "") ));

  setPrimaryKey(reference);
}

Vehicle::Vehicle(QObject *parent, const QJsonObject &json)
  : Vehicle(parent)
{
  update(json);
}

void Vehicle::reset()
{
  reference->setValue(0);
  id_type->setValue(0);
  id_brand->setValue(0);
  id_model->setValue(0);

  type->setValue("");
  brand->setValue("");
  model->setValue("");
  max_w->setValue("");
  vin->setValue("");
  vin_cad->setValue("");
  year->setValue("");
  name->setValue("");

  err->setValue("");
}

}
}

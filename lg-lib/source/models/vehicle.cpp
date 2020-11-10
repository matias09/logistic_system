#include "vehicle.h"

using namespace lg::data;

namespace lg {
namespace models {

Vehicle::Vehicle(QObject *parent)
  : Entity(parent, "vehicles")
{
  reference = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "reference", "Referencia del Vehiculo")
  ) );

  id_type = static_cast<IntDecorator*>(addDataItem(
      new IntDecorator(this, "id_type", "Tipo de Vehiculo")
  ) );

  id_brand = static_cast<IntDecorator*>(addDataItem(
      new IntDecorator(this, "id_brand", "Marca")
  ) );

  id_model = static_cast<IntDecorator*>(addDataItem(
      new IntDecorator(this, "id_model", "Modelo")
  ) );

  max_w = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "max_w", "Max Capacidad de Carga Kg")
  ) );

  vin = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "vin", "Matricula")
  ) );

  vin_cad = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "vin_cad", "Caducidad de la Matricula")
  ) );

  year = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "year", "Año")
  ) );

  type  = "";
  brand = "";
  model = "";

  setPrimaryKey(reference);
}

Vehicle::Vehicle(QObject *parent, const QJsonObject &json)
  : Vehicle(parent)
{
  update(json);
}

}
}

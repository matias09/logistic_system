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

  type = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "type", "Tipo de Vehiculo")
  ) );

  brand = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "brand", "Marca")
  ) );

  model = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "model", "Modelo")
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

  setPrimaryKey(reference);
}

Vehicle::Vehicle(QObject *parent, const QJsonObject &json)
  : Vehicle(parent)
{
  update(json);
}

}
}

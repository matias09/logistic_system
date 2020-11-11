#include "travel.h"

using namespace lg::data;

namespace lg {
namespace models {

Travel::Travel(QObject *parent)
  : Entity(parent, "travels")
{
  reference = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "reference", "Referencia del Viaje") ));

  id_cli = static_cast<IntDecorator*>(addDataItem(
      new IntDecorator(this, "id_cli", "Cliente") ));

  cli = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "cli", "Cliente") ));

  sta_date = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "sta_date", "Fecha de Inicio/Salida") ));

  destiny = static_cast<Destination*>(
      addChild( new Destination(this), "destiny") );

  setPrimaryKey(reference);
}

Travel::Travel(QObject *parent, const QJsonObject &json)
  : Travel(parent)
{
  update(json);
}

}
}

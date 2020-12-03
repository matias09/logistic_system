#include "travel.h"

#include <QDateTime>

using namespace lg::data;

namespace lg {
namespace models {

Travel::Travel(QObject *parent)
  : Entity(parent, "travels")
{
  reference = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "reference", "Referencia del Viaje") ));

  canceled = static_cast<IntDecorator*>(addDataItem(
      new IntDecorator(this, "canceled", "Viaje anulado") ));

  ended = static_cast<IntDecorator*>(addDataItem(
      new IntDecorator(this, "ended", "Viaje finalizado ?") ));

  id_cli = static_cast<IntDecorator*>(addDataItem(
      new IntDecorator(this, "id_cli", "Cliente") ));

  cli = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "cli", "Cliente") ));

  sta_date = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "sta_date", "Fecha de Inicio/Salida") ));
  sta_date->setValue(QDateTime::currentDateTime().toString());

  destiny = static_cast<Destination*>(
      addChild( new Destination(this), "destiny") );

  setPrimaryKey(reference);
}

Travel::Travel(QObject *parent, const QJsonObject &json)
  : Travel(parent)
{
  update(json);
}

void Travel::reset()
{
  reference->setValue(0);
  canceled->setValue(0);
  ended->setValue(0);
  id_cli->setValue(0);
  sta_date->setValue(QDateTime::currentDateTime().toString());

  destiny->reset();
}

}
}

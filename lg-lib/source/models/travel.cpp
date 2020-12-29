#include "travel.h"

#include <QDateTime>

using namespace lg::data;

namespace lg {
namespace models {

Travel::Travel(QObject *parent)
  : Entity(parent, "travels")
{
  reference = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "reference", "Travel ID") ));

  canceled = static_cast<IntDecorator*>(addDataItem(
      new IntDecorator(this, "canceled", "Travel Cancelled ?") ));

  ended = static_cast<IntDecorator*>(addDataItem(
      new IntDecorator(this, "ended", "Travel Ended ?") ));

  id_cli = static_cast<IntDecorator*>(addDataItem(
      new IntDecorator(this, "id_cli", "Client") ));

  cli = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "cli", "Client") ));

  sta_date = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "sta_date", "Start Date") ));

  fin_date = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "fin_date", "End Date") ));

  destiny = static_cast<Destination*>(
      addChild( new Destination(this), "destiny") );

  setPrimaryKey(reference);

  reset();
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

  sta_date->setValue(QDateTime::currentDateTime().toString(Qt::ISODate));
  fin_date->setValue("");

  destiny->reset();
}

}
}

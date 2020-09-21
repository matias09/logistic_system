#include "client.h"

using namespace lg::data;

namespace lg {
namespace models {

Client::Client(QObject *parent)
  : Entity(parent, "client")
{
  reference = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "reference", "Referencia de Cliente")
  ) );

  name = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "name", "Nombre")
  ) );


  phone = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "phone", "Telefono")
  ) );


  cellphone = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "cellphone", "Celular")
  ) );


  mail = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "mail", "E-Mail")
  ) );

  clientAddress = static_cast<Address*>(addChild(new Address(this), "address")  );

  setPrimaryKey(reference);
}

Client::Client(QObject *parent, const QJsonObject &json)
  : Client(parent)
{
  update(json);
}

}
}

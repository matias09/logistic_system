#include "client.h"

using namespace lg::data;

namespace lg {
namespace models {

Client::Client(QObject *parent)
  : Entity(parent, "clients")
{
  reference = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "reference", "Referencia del Cliente")
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


  err = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "error", ""))  );

  err_color = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "error_color", ""))  );

  err_visible = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "error_visible", ""))  );

  setPrimaryKey(reference);
}

Client::Client(QObject *parent, const QJsonObject &json)
  : Client(parent)
{
  update(json);
}

}
}

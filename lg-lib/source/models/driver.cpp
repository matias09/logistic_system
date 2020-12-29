#include "driver.h"

using namespace lg::data;

namespace lg {
namespace models {

Driver::Driver(QObject *parent)
  : Entity(parent, "drivers")
{
  reference = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "reference", "Driver ID")) );

  name = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "name", "Name")) );

  lic_nro = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "lic_nro", "License Number")) );

  lic_cad = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "lic_cad", "Caducity License Date")) );

  phone = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "phone", "Phone")) );


  cellphone = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "cellphone", "Cellphone")) );

  mail = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "mail", "E-Mail")) );

  nro_tra = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "nro_tra", "Number of Travel Realized")) );

  err = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "err", "")) );

  address = static_cast<Address*>(addChild(new Address(this), "address")  );

  setPrimaryKey(reference);
}

Driver::Driver(QObject *parent, const QJsonObject &json)
  : Driver(parent)
{
  update(json);
}

void Driver::reset()
{
  reference->setValue(0);

  name->setValue("");
  lic_nro->setValue("");
  lic_cad->setValue("");
  phone->setValue("");
  cellphone->setValue("");
  mail->setValue("");
  err->setValue("");

  address->reset();
}

}
}

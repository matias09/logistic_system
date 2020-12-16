#include "driver.h"

using namespace lg::data;

namespace lg {
namespace models {

Driver::Driver(QObject *parent)
  : Entity(parent, "drivers")
{
  reference = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "reference", "Referencia del Chofer")) );

  name = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "name", "Nombre")) );

  lic_nro = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "lic_nro", "Nro de Licencia")) );

  lic_cad = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "lic_cad", "Fecha de Cad. de Licencia")) );

  phone = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "phone", "Telefono")) );


  cellphone = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "cellphone", "Celular")) );

  mail = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "mail", "E-Mail")) );

  nro_tra = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "nro_tra", "Nro de Viajes Realizados")) );

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

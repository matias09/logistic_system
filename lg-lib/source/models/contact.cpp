#include "contact.h"

using namespace lg::data;

namespace lg {
namespace models {

Contact::Contact(QObject *parent)
  : Entity (parent, "constact")
{
  type = static_cast<EnumeratorDecorator*>(addDataItem(
      new EnumeratorDecorator(this, "type", "Type", 0, contactTypeMapper)
  ) );

  address = static_cast<StringDecorator*>(addDataItem(
      new StringDecorator(this, "address", "Address")
  ) );
}

Contact::Contact(QObject *parent, const QJsonObject &json)
  : Contact(parent)
{
  update(json);
}

} //  models
} //  lg

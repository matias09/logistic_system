#ifndef CONTACT_H
#define CONTACT_H

#include <QObject>

#include <lg-lib_global.h>
#include <data/stringdecorator.h>
#include <data/enumeratordecorator.h>
#include <data/entity.h>

namespace lg {
namespace models {

class LGLIBSHARED_EXPORT Contact : public data::Entity
{
  Q_OBJECT
  Q_PROPERTY(lg::data::EnumeratorDecorator* ui_type MEMBER type CONSTANT)
  Q_PROPERTY(lg::data::StringDecorator* ui_address MEMBER address CONSTANT)

public:
  enum eContactType {
    Unknown =0
   ,Telephone
   ,Email
   ,Fax
  };

  explicit Contact(QObject *parent = nullptr);
  Contact(QObject *parent, const QJsonObject &json);

  data::EnumeratorDecorator* type{nullptr};
  data::StringDecorator* address{nullptr};

private:
  std::map<int, QString> contactTypeMapper = std::map<int, QString>
  {
    { Contact::eContactType::Unknown, "" }
   ,{ Contact::eContactType::Telephone, "Telephone" }
   ,{ Contact::eContactType::Email, "Email" }
   ,{ Contact::eContactType::Fax, "Fax" }
  };

};

}
}

#endif // CONTACT_H

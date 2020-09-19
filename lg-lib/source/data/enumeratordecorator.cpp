#include "enumeratordecorator.h"

#include <QVariant>

namespace lg {
namespace data {

class EnumeratorDecorator::Implementation
{
public:
  Implementation(
                EnumeratorDecorator *_enumeratorDecorator
               , const int  _value = 0
               , const std::map<int, QString>& _descriptionMapper = std::map<int, QString>() )
   : enumeratorDecorator(_enumeratorDecorator)
    ,value(_value)
    ,descriptionMapper(_descriptionMapper) {}

    EnumeratorDecorator* enumeratorDecorator{nullptr};
     int  value;
     const std::map<int, QString>  descriptionMapper;
};

 EnumeratorDecorator::EnumeratorDecorator(
             Entity* parentEntity
           , const QString &key
           , const QString &label
           , const int  value
           , const std::map<int, QString>& descriptionMapper )
  : DataDecorator (parentEntity, key, label)
 {
    implementation.reset( new Implementation(this, value) );
 }

 EnumeratorDecorator::~EnumeratorDecorator(){}

 int EnumeratorDecorator::value() const
{
    return implementation->value;
}

EnumeratorDecorator& EnumeratorDecorator::setValue(const int value)
{
   if (value != implementation->value) {
    // .... validation here if required ...
      implementation->value = value;
      emit valueChanged();
   }

   return *this;
}

QString  EnumeratorDecorator::valueDescription() const
{
  if (implementation->descriptionMapper.find( implementation->value )
      !=
      implementation->descriptionMapper.end()
  ) {
    return implementation->descriptionMapper.at( implementation->value );
  } else {
    return {};
  }
}

QJsonValue EnumeratorDecorator::jsonValue() const
{
  return QJsonValue::fromVariant( QVariant(implementation->value) );
}

void EnumeratorDecorator::update(const QJsonObject &_jsonObject)
{
  if (_jsonObject.contains( key() ) ) {
    setValue( _jsonObject.value( key() ).toInt() );
  } else {
    setValue(0);
  }
}

} // data
} // lg

#include "combooption.h"

namespace lg {
namespace data {

class ComboOption::Implementation
{
public:
  Implementation( const QString &_value
                 ,const QString &_desc)
    : value(_value)
     ,desc(_desc) {}

  const QString value;
  const QString desc;
};

ComboOption::ComboOption(QObject* parent
                        ,const QString &value
                        ,const QString &desc
  ) : QObject (parent)
  {
     implementation.reset(new Implementation(value, desc) );
  }

ComboOption::~ComboOption() {}

const QString& ComboOption::value() const
{
    return implementation->value;
}

const QString& ComboOption::desc() const
{
    return implementation->desc;
}

} // models
} // lg


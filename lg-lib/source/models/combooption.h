#ifndef COMBOOPTION_H
#define COMBOOPTION_H

#include <QObject>
#include <QString>

#include <lg-lib_global.h>

namespace lg {
namespace models {

class LGLIBSHARED_EXPORT ComboOption : public QObject
{
  Q_OBJECT
  Q_PROPERTY( QString ui_value MEMBER value CONSTANT )
  Q_PROPERTY( QString ui_desc  MEMBER desc  CONSTANT )

public:
  explicit ComboOption(
       QObject *parent = nullptr
      ,const QString &_value = ""
      ,const QString &_desc  = "" )
  : QObject (parent)
   ,value(_value)
   ,desc(_desc) {};

  ~ComboOption() {};

  QString value;
  QString desc;

signals:

private:
};

} // framework
} // lg

#endif // COMBOOPTION_H

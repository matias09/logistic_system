#ifndef COMBOOPTION_H
#define COMBOOPTION_H

#include <QObject>
#include <QString>
#include <QScopedPointer>

#include <lg-lib_global.h>

namespace lg {
namespace models {

class LGLIBSHARED_EXPORT ComboOption : public QObject
{
  Q_OBJECT
  Q_PROPERTY( QString ui_value READ value CONSTANT )
  Q_PROPERTY( QString ui_desc  READ desc  CONSTANT )

public:
  explicit ComboOption(
       QObject *parent = nullptr
      ,const QString &_value = ""
      ,const QString &_desc  = "" );

  ~ComboOption();

  const QString& value() const;
  const QString& desc() const;

private:
  class Implementation;
  QScopedPointer<Implementation> implementation;
};

} // framework
} // lg

#endif // COMBOOPTION_H

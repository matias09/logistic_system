#ifndef STRINGDECORATOR_H
#define STRINGDECORATOR_H

#include <QJsonObject>
#include <QJsonValue>
#include <QObject>
#include <QScopedPointer>
#include <QString>

#include <lg-lib_global.h>
#include <data/datadecorator.h>

namespace lg {
namespace data {

class LGLIBSHARED_EXPORT StringDecorator : public DataDecorator
{
  Q_OBJECT
  Q_PROPERTY( QString ui_value READ value WRITE setValue NOTIFY valueChanged )

public:
  StringDecorator(
     Entity* parentEntity = nullptr
   , const QString &key = "SomeKey"
   , const QString &label = ""
   , const QString &value = "" );

   ~StringDecorator() override;

   StringDecorator& setValue(const QString &value);
   const QString& value() const;

   QJsonValue jsonValue() const override;
   void update(const QJsonObject &jsonObject) override;

signals:
  void valueChanged();

 private:
  class Implementation;
  QScopedPointer<Implementation> implementation;
};

} // data
} // lg

#endif // STRINGDECORATOR_H


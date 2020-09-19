#ifndef IDATABASECONTROLLER_H
#define IDATABASECONTROLLER_H

#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QObject>
#include <QString>

#include <lg-lib_global.h>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT IDatabaseController : public QObject
{
  Q_OBJECT

public:
  IDatabaseController(QObject *parent)  : QObject (parent){}
  virtual ~IDatabaseController() {}

  virtual bool createRow(
      const QString &tableName
     ,const QString &id
     ,const QJsonObject &jsonObject) const = 0;

  virtual bool deleteRow(
    const QString &tableName,
    const QString &id) const = 0;

  virtual QJsonArray find(
    const QString &tableName,
    const QString &searchText) const = 0;

  virtual QJsonObject readRow(
    const QString &tableName
   ,const QString &id) const = 0;

  virtual bool updateRow(
    const QString &tableName
   ,const QString &id
   ,const QJsonObject &jsonObject) const = 0;

};

} // namespace controllers
} // namespace lg
#endif // IDATABASECONTROLLER_H

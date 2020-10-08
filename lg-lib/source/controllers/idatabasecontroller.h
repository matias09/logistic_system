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

  virtual bool createClient(
      const QString &id
     ,const QJsonObject &jsonObject) const = 0;

  virtual bool deleteClient(const QString &id) const = 0;

  virtual QJsonArray findClientByName(const QString &searchText) const = 0;

  virtual bool updateClient(
    const QString &id
   ,const QJsonObject &jsonObject) const = 0;

  virtual  bool createDriver(const QString &id
                   ,const QJsonObject &jsonObject) const = 0;
  virtual  bool deleteDriver(const QString &id) const = 0;
  virtual QJsonArray findDriverByName(const QString &searchText) const = 0;
  virtual bool updateDriver(const QString &id
                  ,const QJsonObject &jsonObject) const = 0;
};

} // namespace controllers
} // namespace lg
#endif // IDATABASECONTROLLER_H

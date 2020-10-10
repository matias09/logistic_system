#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include <QObject>
#include <QScopedPointer>
#include <QJsonObject>

#include <lg-lib_global.h>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT DatabaseController : public QObject
{
  Q_OBJECT
public:
  explicit DatabaseController();
  ~DatabaseController();

  const QSqlDatabase& getDatabaseConn() const;

  bool create(const QString &sqlStatement
             ,const std::map<QString, QVariant> &binds) const;

  QSqlQuery search(const QString &sqlStatement
                  ,const std::map<QString, QVariant> &binds) const;

  bool update(const QString &sqlStatement
             ,const std::map<QString, QVariant> &binds) const;

  bool remove(const QString &sqlStatement
             ,const std::map<QString, QVariant> &binds) const;


  bool createDriver(const QString &id
                   ,const QJsonObject &jsonObject) const;
  bool deleteDriver(const QString &id) const;
  QJsonArray findDriverByName(const QString &searchText) const;
  bool updateDriver(const QString &id
                  ,const QJsonObject &jsonObject) const;

private:
  class Implementation;
  QScopedPointer<Implementation> implementation;
};

} //  controllers
} // lg
#endif // DATABASECONTROLLER_H





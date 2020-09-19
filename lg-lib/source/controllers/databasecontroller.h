#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <QScopedPointer>

#include <controllers/idatabasecontroller.h>
#include <lg-lib_global.h>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT DatabaseController : public IDatabaseController
{
  Q_OBJECT
public:
  explicit DatabaseController(QObject *parent = nullptr);
  ~DatabaseController() override;

    bool createRow(
       const QString &tableName
      ,const QString &id
      ,const QJsonObject &jsonObject) const override;

    bool deleteRow( const QString &tableName, const QString &id) const override;

   QJsonArray find( const QString &tableName, const QString &searchText) const override;
   QJsonObject readRow(const QString &tableName, const QString &id) const override;

   bool updateRow(
      const QString &tableName
     ,const QString &id
     ,const QJsonObject &jsonObject) const override;

private:
  class Implementation;
  QScopedPointer<Implementation> implementation;
};

} //  controllers
} // lg
#endif // DATABASECONTROLLER_H

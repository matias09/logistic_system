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

    bool createClient(const QString &id
                     ,const QJsonObject &jsonObject) const override;
    bool deleteClient(const QString &id) const override;
   QJsonArray findClientByName(const QString &searchText) const override;
   bool updateClient(const QString &id
                    ,const QJsonObject &jsonObject) const override;


    bool createDriver(const QString &id
                     ,const QJsonObject &jsonObject) const override;
    bool deleteDriver(const QString &id) const override;
   QJsonArray findDriverByName(const QString &searchText) const override;
   bool updateDriver(const QString &id
                    ,const QJsonObject &jsonObject) const override;

private:
  class Implementation;
  QScopedPointer<Implementation> implementation;
};

} //  controllers
} // lg
#endif // DATABASECONTROLLER_H

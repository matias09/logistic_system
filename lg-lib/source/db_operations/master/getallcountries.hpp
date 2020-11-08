#ifndef GET_ALL_COUNTRIES_H
#define GET_ALL_COUNTRIES_H

#include <controllers/databasecontroller.h>
#include <controllers/mastercontroller.h>
#include <models/combooption.h>

#include <QJsonObject>
#include <QList>

#include <lg-lib_global.h>

#include <iostream>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT MasterController::GetAllCountries
{
public:
  static QList<models::ComboOption*> call(
      QObject &parent
     ,const controllers::DatabaseController &db)
  { return GetAllCountries().exec(parent, db); }

private:
  QList<models::ComboOption*> exec(
      QObject &parent
     ,const controllers::DatabaseController &db)
  {
    QString sqlStm = "SELECT id, name FROM countries";

    QSqlQuery&& query = db.search(sqlStm, {});

    QList<models::ComboOption*> cl{};
    while ( query.next() ) {
      models::ComboOption* co = new models::ComboOption(
        &parent
       ,query.value(0).toString()
       ,query.value(1).toString() );

      cl.append(co);
    }

    return cl;
  }

  GetAllCountries() = default;
  GetAllCountries(const GetAllCountries&) = delete;
  GetAllCountries& operator =(const GetAllCountries&) = delete;

  GetAllCountries(const GetAllCountries&&) = delete;
  ~GetAllCountries() = default;
};

} //  models {
} // lg

#endif  // GET_ALL_COUNTRIES_H

#ifndef FIND_VEHICLE_BY_BRAND_H
#define FIND_VEHICLE_BY_BRAND_H

#include <controllers/databasecontroller.h>
#include <models/vehiclesearch.h>

#include <QJsonObject>
#include <QJsonArray>

#include <lg-lib_global.h>

#include <iostream>

namespace lg {
namespace models {

class LGLIBSHARED_EXPORT VehicleSearch::FindByBrand
{
public:
  static bool call(QJsonArray &returnValue
                  ,const QString &searchText
                  ,const controllers::DatabaseController &db)
  { return FindByBrand().exec(returnValue, searchText, db); }

private:
  bool exec(QJsonArray &returnValue
           ,const QString &searchText
           ,const controllers::DatabaseController &db)
  {
    if ( searchText.isEmpty() ) return false;

    QString sqlStm = "                                              \
    SELECT b.id as id_brand, m.id as id_model, vt.id as id_type     \
          ,v.id, v.max_weight ,v.vin, v.vin_cad_date, v.year        \
          ,b.name, m.name, vt.name                                  \
    FROM vehicles v                                                 \
    INNER JOIN vehicle_types vt ON (v.id_type_vehicle = vt.id)      \
    INNER JOIN models m ON (v.id_model = m.id)                      \
    INNER JOIN brands b ON (m.id_brand = b.id)                      \
    WHERE LOWER(b.name) LIKE :searchText ";

    std::map<QString, QVariant> binds;
    binds.insert(std::pair<QString, QVariant>(
                  ":searchText",
                  QVariant("%" + searchText.toLower() + "%") ));

    QSqlQuery&& query = db.search(sqlStm, binds);

    while ( query.next() ) {
      QJsonObject jsonObj;

      jsonObj.insert("id_brand",     query.value(0).toInt() );
      jsonObj.insert("id_model",     query.value(1).toInt() );
      jsonObj.insert("id_type",      query.value(2).toInt() );

      jsonObj.insert("reference", query.value(3).toString() );
      jsonObj.insert("max_w",     query.value(4).toString() );
      jsonObj.insert("vin",       query.value(5).toString() );
      jsonObj.insert("vin_cad" ,  query.value(6).toString() );
      jsonObj.insert("year",      query.value(7).toString() );

      jsonObj.insert("brand",     query.value(8).toString() );
      jsonObj.insert("model",     query.value(9).toString() );
      jsonObj.insert("type",      query.value(10).toString() );

      returnValue.append( jsonObj );
    }

    return true;
  }

  FindByBrand() = default;
  FindByBrand(const FindByBrand&) = delete;
  FindByBrand& operator =(const FindByBrand&) = delete;

  FindByBrand(const FindByBrand&&) = delete;
  ~FindByBrand() = default;
};

} //  models {
} // lg

#endif  // FIND_VEHICLE_BY_NAME_H

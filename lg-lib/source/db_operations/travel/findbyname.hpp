#ifndef FIND_BY_NAME_H
#define FIND_BY_NAME_H

#include <controllers/databasecontroller.h>
#include <models/travelsearch.h>

#include <QJsonObject>
#include <QJsonArray>

#include <lg-lib_global.h>

#include <iostream>

namespace lg {
namespace models {

class LGLIBSHARED_EXPORT TravelSearch::FindByName
{
public:
  static bool call(QJsonArray &returnValue
                  ,const QString &searchText
                  ,const controllers::DatabaseController &db)
  { return FindByName().exec(returnValue, searchText, db); }

private:
  bool exec(QJsonArray &returnValue
           ,const QString &searchText
           ,const controllers::DatabaseController &db)
  {
    if ( searchText.isEmpty() ) return false;

    QString sqlStm =
         " SELECT t.id, t.id_client, t.sta_date "
         "    ,d.id_driver, d.id_vehicle ,d.arrival_date "
         "    ,d.street, d.house_nro, d.post_code  "
         "  FROM travels t "
         "  INNER JOIN travels_destinations td ON (t.id = td.id_travel) "
         "  INNER JOIN destinations d          ON (td.id_destination = d.id) "
         " WHERE LOWER(name) LIKE :searchText" ;

    std::map<QString, QVariant> binds;
    binds.insert(std::pair<QString, QVariant>(
                  ":searchText",
                  QVariant("%" + searchText.toLower() + "%") ));

    QSqlQuery&& query = db.search(sqlStm, binds);

    while ( query.next() ) {
      QJsonObject jsonObjAddress;
      jsonObjAddress.insert("street",    query.value(7).toString() );
      jsonObjAddress.insert("house_nro", query.value(8).toString() );
      jsonObjAddress.insert("postcode",  query.value(9).toString() );

      QJsonObject jsonObjDestination;
      jsonObj.insert("id_dri",     query.value(4).toString() );
      jsonObj.insert("id_veh",     query.value(5).toString() );
      jsonObj.insert("arr_date",   query.value(6).toString() );
      jsonObj.insert("address", jsonObjAddress );

      QJsonObject jsonObj;
      jsonObj.insert("reference", query.value(1).toString() );
      jsonObj.insert("id_client", query.value(2).toString() );
      jsonObj.insert("sta_date",  query.value(3).toString() );
      jsonObj.insert("destiny", jsonObjDestination );

      returnValue.append( jsonObj );
    }

    return true;
  }

  FindByName() = default;
  FindByName(const FindByName&) = delete;
  FindByName& operator =(const FindByName&) = delete;

  FindByName(const FindByName&&) = delete;
  ~FindByName() = default;
};

} //  models {
} // lg

#endif  // FIND_BY_NAME_H

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

class LGLIBSHARED_EXPORT TravelSearch::FindByClientName
{
public:
  static bool call(QJsonArray &returnValue
                  ,const QString &searchText
                  ,const controllers::DatabaseController &db)
  { return FindByClientName().exec(returnValue, searchText, db); }

private:
  bool exec(QJsonArray &returnValue
           ,const QString &searchText
           ,const controllers::DatabaseController &db)
  {
    if ( searchText.isEmpty() ) return false;

    QString sqlStm =
         " SELECT t.id, t.id_client, t.sta_date "
         "    ,d.id ,d.id_driver, d.id_vehicle, d.arrival_date "
         "    ,d.street, d.house_nro, d.post_code, c.name, d.id_state, s.name "
         "    ,dr.name, v.name, t.ended, t.canceled "
         "  FROM travels t "
         "  INNER JOIN travels_destinations td ON (t.id = td.id_travel) "
         "  INNER JOIN destinations d          ON (td.id_destination = d.id) "
         "  INNER JOIN clients c               ON (t.id_client = c.id) "
         "  INNER JOIN states s                ON (d.id_state = s.id) "
         "  INNER JOIN drivers dr              ON (dr.id = d.id_driver) "
         "  INNER JOIN vehicles v              ON (v.id = d.id_vehicle) "
         " WHERE LOWER(c.name) LIKE :searchText" ;

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
      jsonObjAddress.insert("id_state",  query.value(11).toInt() );
      jsonObjAddress.insert("state",     query.value(12).toString() );

      QJsonObject jsonObjDestination;
      jsonObjDestination.insert("reference",  query.value(3).toString() );
      jsonObjDestination.insert("id_dri",     query.value(4).toInt() );
      jsonObjDestination.insert("id_veh",     query.value(5).toInt() );
      jsonObjDestination.insert("dri",        query.value(13).toString() );
      jsonObjDestination.insert("veh",        query.value(14).toString() );

      jsonObjDestination.insert("id_dri_o",     query.value(4).toInt() );
      jsonObjDestination.insert("id_veh_o",     query.value(5).toInt() );

      jsonObjDestination.insert("arr_date",   query.value(6).toString() );
      jsonObjDestination.insert("address", jsonObjAddress );

      QJsonObject jsonObj;
      jsonObj.insert("reference", query.value(0).toString() );
      jsonObj.insert("ended",     query.value(15).toInt() );
      jsonObj.insert("canceled",  query.value(16).toInt() );
      jsonObj.insert("id_cli",    query.value(1).toInt() );
      jsonObj.insert("sta_date",  query.value(2).toString() );
      jsonObj.insert("cli",       query.value(10).toString() );
      jsonObj.insert("destiny", jsonObjDestination );

      returnValue.append( jsonObj );
    }

    return true;
  }

  FindByClientName() = default;
  FindByClientName(const FindByClientName&) = delete;
  FindByClientName& operator =(const FindByClientName&) = delete;

  FindByClientName(const FindByClientName&&) = delete;
  ~FindByClientName() = default;
};

} //  models {
} // lg

#endif  // FIND_BY_NAME_H

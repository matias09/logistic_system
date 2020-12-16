#ifndef FIND_BY_NAME_H
#define FIND_BY_NAME_H

#include <controllers/databasecontroller.h>
#include <models/driversearch.h>

#include <QJsonObject>
#include <QJsonArray>

#include <lg-lib_global.h>

#include <iostream>

namespace lg {
namespace models {

class LGLIBSHARED_EXPORT DriverSearch::FindByName
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
    QString sqlStm =
      "SELECT id, name, phone, lic_nro, lic_caducity_date "
      " ,cellphone, mail, street "
      " ,house_nro, post_code, id_state, nro_travels "
      "  FROM drivers ";

    if ( not searchText.isEmpty() ) {
      sqlStm.append(" WHERE LOWER(name) LIKE :searchText ");
    }

    std::map<QString, QVariant> binds;
    binds.insert(std::pair<QString, QVariant>(
                  ":searchText",
                  QVariant("%" + searchText.toLower() + "%") ));

    QSqlQuery&& query = db.search(sqlStm, binds);

    while ( query.next() ) {
      QJsonObject jsonObj;

      jsonObj.insert("reference", query.value(0).toString() );
      jsonObj.insert("name",      query.value(1).toString() );
      jsonObj.insert("phone",     query.value(2).toString() );
      jsonObj.insert("lic_nro",   query.value(3).toString() );
      jsonObj.insert("lic_cad",   query.value(4).toString() );
      jsonObj.insert("cellphone", query.value(5).toString() );
      jsonObj.insert("mail",      query.value(6).toString() );
      jsonObj.insert("nro_tra",   query.value(11).toString() );

      QJsonObject jsonObjAddress;
      jsonObjAddress.insert("street",    query.value(7).toString() );
      jsonObjAddress.insert("house_nro", query.value(8).toString() );
      jsonObjAddress.insert("postcode",  query.value(9).toString() );
      jsonObjAddress.insert("id_state",  query.value(10).toInt() );

      jsonObj.insert("address", jsonObjAddress );

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

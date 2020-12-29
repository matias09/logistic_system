#ifndef FIND_CLIENT_BY_NAME_H
#define FIND_CLIENT_BY_NAME_H

#include <controllers/databasecontroller.h>
#include <models/clientsearch.h>

#include <QJsonObject>
#include <QJsonArray>

#include <lg-lib_global.h>

namespace lg {
namespace models {

class LGLIBSHARED_EXPORT ClientSearch::FindByName
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
    QString sqlStm = " SELECT "
      "  c.id, c.name, c.phone, c.cellphone, c.mail, c.street "
      " ,c.house_nro, c.post_code, c.id_state, s.name "
      "  FROM clients c "
      "  INNER JOIN  states s ON (c.id_state = s.id) ";

    if ( not searchText.isEmpty() ) {
      sqlStm.append(" WHERE LOWER(c.name) LIKE :searchText ");
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
      jsonObj.insert("cellphone", query.value(3).toString() );
      jsonObj.insert("mail",      query.value(4).toString() );

      QJsonObject jsonObjAddress;
      jsonObjAddress.insert("street",    query.value(5).toString() );
      jsonObjAddress.insert("house_nro", query.value(6).toString() );
      jsonObjAddress.insert("postcode",  query.value(7).toString() );
      jsonObjAddress.insert("id_state",  query.value(8).toInt() );
      jsonObjAddress.insert("state",     query.value(9).toString() );

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

#endif  // FIND_CLIENT_BY_NAME_H

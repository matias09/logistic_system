#ifndef FIND_BY_NAME_H
#define FIND_BY_NAME_H

#include <models/clientsearch.h>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

#include <QJsonObject>
#include <QJsonArray>

#include <lg-lib_global.h>

#include <iostream>

namespace lg {
namespace models {

class LGLIBSHARED_EXPORT ClientSearch::FindByName
{
public:
  static bool call(QJsonArray &returnValue,
                   const QString &searchText,
                   const QSqlDatabase &database)
  { return FindByName().exec(returnValue, searchText, database); }

private:
  bool exec(QJsonArray &returnValue
           ,const QString &searchText
           ,const QSqlDatabase &database)
  {
    if ( searchText.isEmpty() ) return false;

    QSqlQuery query(database);
    QString sqlStatement = "SELECT id, name, phone, cellphone, mail, street, "
      " house_nro, post_code "
      "  FROM clients "
      " WHERE LOWER(name) LIKE :searchText" ;

    query.prepare(sqlStatement);
    if ( query.lastError().type() != QSqlError::NoError ) {
      std::cout << "Can't Select Client: "
                << query.lastError().text().toStdString() << std::endl;
      return false;
    }

    query.bindValue(":searchText", QVariant("%" + searchText.toLower() + "%") );

    query.exec();
    if ( query.lastError().type() != QSqlError::NoError ) {
      std::cout << "Can't Select Client: "
                << query.lastError().text().toStdString() << std::endl;
      return false;
    }

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
      jsonObjAddress.insert("postcode", query.value(7).toString() );

      jsonObj.insert("address",      jsonObjAddress );

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

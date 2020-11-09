#ifndef INSERT_CLIENT_H
#define INSERT_CLIENT_H

#include <controllers/databasecontroller.h>
#include <controllers/clicommandcontroller.h>

#include <QJsonObject>

#include <lg-lib_global.h>

#include <iostream>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT CliCommandController::Insert
{
  typedef std::pair<QString, QVariant> Burden;
public:
  static bool call(const QJsonObject &jo
                  ,const controllers::DatabaseController &db)
  { return Insert().exec(jo, db); }

private:
  bool exec(const QJsonObject &jo
           ,const controllers::DatabaseController &db)
  {
    if ( jo.isEmpty() ) return false;

    QString sqlStm = "INSERT INTO clients "
     " (id_state, name, phone, cellphone, mail , street, house_nro, post_code) "
     "  VALUES "
     " (:id_state, :name, :phone, :cellphone, :mail "
     " ,:street, :house_nro, :post_code )";


    std::cout << "state id: "
              << jo["address"]["id_state"].toInt()
              << std::endl;

    std::map<QString, QVariant> binds;
    binds.insert(Burden(":name",      QVariant(jo["name"])) );
    binds.insert(Burden(":phone",     QVariant(jo["phone"])) );
    binds.insert(Burden(":cellphone", QVariant(jo["cellphone"])) );
    binds.insert(Burden(":mail",      QVariant(jo["mail"])) );
    binds.insert(Burden(":street",    QVariant(jo["address"]["street"])) );
    binds.insert(Burden(":house_nro", QVariant(jo["address"]["house_nro"])) );
    binds.insert(Burden(":post_code", QVariant(jo["address"]["postcode"])) );
    binds.insert(Burden(":id_state",
                QVariant(jo["address"]["id_state"].toInt() )) );

    return  db.create(sqlStm, binds);
  }

  Insert() = default;
  Insert(const Insert&) = delete;
  Insert& operator =(const Insert&) = delete;

  Insert(const Insert&&) = delete;
  ~Insert() = default;
};

} //  controllers
} // lg

#endif  // INSERT_CLIENT_H

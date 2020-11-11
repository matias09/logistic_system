#ifndef UPDATE_BY_ID_H
#define UPDATE_BY_ID_H

#include <controllers/databasecontroller.h>
#include <controllers/dricommandcontroller.h>

#include <QJsonObject>

#include <lg-lib_global.h>

#include <iostream>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT DriCommandController::UpdateById
{
  typedef std::pair<QString, QVariant> Burden;
public:
  static bool call(const QJsonObject &jo
                  ,const QString &id
                  ,const controllers::DatabaseController &db)
  { return UpdateById().exec(jo, id, db); }

private:
  bool exec(const QJsonObject &jo
           ,const QString &id
           ,const controllers::DatabaseController &db)
  {
    if ( id.isEmpty() ) return false;

    QString sqlStm = "UPDATE drivers "
     "  SET "
     "   id_state = :id_state, name = :name, phone = :phone "
     " , lic_nro = :lic_nro, lic_caducity_date = :lic_cad "
     " , cellphone = :cellphone, mail = :mail, street = :street "
     " , house_nro = :house_nro, post_code = :post_code "
     "  WHERE id = :id";

    std::map<QString, QVariant>  binds;
    binds.insert(Burden(":id",        QVariant(id.toInt()) ));
    binds.insert(Burden(":name",      QVariant(jo["name"]) ));
    binds.insert(Burden(":phone",     QVariant(jo["phone"]) ));
    binds.insert(Burden(":lic_nro",   QVariant(jo["lic_nro"]) ));
    binds.insert(Burden(":lic_cad",   QVariant(jo["lic_cad"].toString()) ));
    binds.insert(Burden(":cellphone", QVariant(jo["cellphone"]) ));
    binds.insert(Burden(":mail",      QVariant(jo["mail"]) ));
    binds.insert(Burden(":street",    QVariant(jo["address"]["street"]) ));
    binds.insert(Burden(":house_nro", QVariant(jo["address"]["house_nro"]) ));
    binds.insert(Burden(":post_code", QVariant(jo["address"]["postcode"]) ));
    binds.insert(Burden(":id_state",
                 QVariant(jo["address"]["id_state"].toInt())) );

    return db.update(sqlStm, binds);
  }

  UpdateById() = default;
  UpdateById(const UpdateById&) = delete;
  UpdateById& operator =(const UpdateById&) = delete;

  UpdateById(const UpdateById&&) = delete;
  ~UpdateById() = default;
};

} //  controllers
} // lg

#endif  // UPDATE_BY_ID_H

#ifndef UPDATE_BY_ID_H
#define UPDATE_BY_ID_H

#include <controllers/databasecontroller.h>
#include <controllers/tracommandcontroller.h>

#include <QJsonObject>

#include <lg-lib_global.h>

#include <iostream>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT TraCommandController::UpdateById
{
  typedef std::pair<QString, QVariant> Burden;
public:
  static bool call(      QString     &err
                  ,const QJsonObject &jo
                  ,const controllers::DatabaseController &db)
  { return UpdateById(err, jo, db).exec(); }

private:
  bool exec()
  {
    if ( jo_.isEmpty() ) return false;

    QSqlDatabase::database().transaction();

    if ( not updateDestinations() || not updateTravel() ) {
      err_.append("Los datos cargados no son validos");

      QSqlDatabase::database().rollback();
      return false;
    }

    unsigned int cid = jo_["destiny"]["id_dri"].toInt();
    unsigned int oid = jo_["destiny"]["id_dri_o"].toInt();

    if ( cid != oid ) {
      if ( not unblockDriver() || not blockDriver() ) {
        QSqlDatabase::database().rollback();
        return false;
      }
    }

    cid = jo_["destiny"]["id_veh"].toInt();
    oid = jo_["destiny"]["id_veh_o"].toInt();

    if ( cid != oid ) {
      if ( not unblockVehicle() || not blockVehicle() ) {
        QSqlDatabase::database().rollback();
        return false;
      }
    }

    QSqlDatabase::database().commit();
    return true;
  }

  bool updateDestinations()
  {
    QString sqlStm = "UPDATE destinations "
    "  SET "
    "  id_driver = :id_driver, id_vehicle = :id_vehicle, id_state = :id_state "
    " ,arrival_date = :arrival_date, street = :street   "
    " ,house_nro = :house_nro, post_code = :post_code   "
    " WHERE id = :id_destination";

    std::map<QString, QVariant>  binds;
    binds.insert(Burden(":id_destination",
          QVariant(jo_["destiny"]["reference"]) ));

    binds.insert(Burden(":id_driver", QVariant(jo_["destiny"]["id_dri"].toInt()) ));
    binds.insert(Burden(":id_vehicle",QVariant(jo_["destiny"]["id_veh"].toInt()) ));

    binds.insert(Burden(":arrival_date",
          QVariant(jo_["destiny"]["arr_date"]) ));

    binds.insert(Burden(":id_state",
          QVariant(jo_["destiny"]["address"]["id_state"].toInt())) );
    binds.insert(Burden(":street",
          QVariant(jo_["destiny"]["address"]["street"]) ));
    binds.insert(Burden(":house_nro",
          QVariant(jo_["destiny"]["address"]["house_nro"]) ));
    binds.insert(Burden(":post_code",
          QVariant(jo_["destiny"]["address"]["postcode"]) ));

    return db_.update(sqlStm, binds);
  }

  bool updateTravel()
  {
    const unsigned int not_canceled = 0;
    QString sqlStm = "UPDATE travels "
     "  SET "
     "   id_client = :id_client, sta_date = :sta_date, ended = :ended "
     "  WHERE id = :id AND canceled = :canceled";

    std::map<QString, QVariant>  binds;
    binds.insert(Burden(":id",        QVariant(jo_["reference"]) ));
    binds.insert(Burden(":id_client", QVariant(jo_["id_cli"].toInt()) ));
    binds.insert(Burden(":sta_date",  QVariant(jo_["sta_date"]) ));
    binds.insert(Burden(":ended",     QVariant(jo_["ended"].toInt()) ));
    binds.insert(Burden(":canceled",  not_canceled ));

    return db_.update(sqlStm, binds);
  }

  bool unblockDriver() const
  {
    QString sqlStm = "UPDATE drivers SET blocked = 0 WHERE  id = :id ";

    std::map<QString, QVariant> binds;
    binds.insert(Burden(":id", QVariant(jo_["destiny"]["id_dri_o"].toInt())) );

    return  db_.update(sqlStm, binds);
  }

  bool unblockVehicle() const
  {
    QString sqlStm = "UPDATE vehicles SET blocked = 0 WHERE  id = :id ";

    std::map<QString, QVariant> binds;
    binds.insert(Burden(":id", QVariant(jo_["destiny"]["id_veh_o"].toInt())) );

    return  db_.update(sqlStm, binds);
  }

  bool blockDriver() const
  {
    QString sqlStm = "UPDATE drivers SET blocked = 1 WHERE  id = :id ";

    std::map<QString, QVariant> binds;
    binds.insert(Burden(":id", QVariant(jo_["destiny"]["id_dri"].toInt())) );

    if ( db_.update(sqlStm, binds) == false ) {
      err_.append("El Conductor seleccionado No Existe");
      return false;
    }

    return true;
  }

  bool blockVehicle() const
  {
    QString sqlStm = "UPDATE vehicles SET blocked = 1 WHERE  id = :id ";

    std::map<QString, QVariant> binds;
    binds.insert(Burden(":id", QVariant(jo_["destiny"]["id_veh"].toInt())) );

    if ( db_.update(sqlStm, binds) == 0) {
      err_.append("El Vehiculo seleccionado No Existe");
      return false;
    }

    return true;
  }

  UpdateById(QString &err
            ,const QJsonObject &jo
            ,const controllers::DatabaseController &db)
    : err_(err)
     ,jo_(jo)
     ,db_(db) {}

  UpdateById(const UpdateById&) = delete;
  UpdateById& operator =(const UpdateById&) = delete;

  UpdateById(const UpdateById&&) = delete;
  ~UpdateById() = default;

  QString &err_;
  const QJsonObject &jo_;
  const controllers::DatabaseController &db_;
};

} //  controllers
} // lg

#endif  // UPDATE_BY_ID_H

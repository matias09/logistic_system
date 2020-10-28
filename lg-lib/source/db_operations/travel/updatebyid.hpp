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
  static bool call(const QJsonObject &jo
                  ,const QString &id
                  ,const controllers::DatabaseController &db)
  { return UpdateById(jo, id, db).exec(); }

private:
  bool exec()
  {
    if ( jo_.isEmpty() ) return false;

    /// Horrible needed code to validate IF use choose a  blocked driver
    /// because we didn't implemented the DropDown Menu ( Combo Box )
    if ( jo_["destiny"]["id_dri"] != jo_["destiny"]["id_dri_o"] ) {
      if ( driverIsBlocked() ) {
        std::cout << "Driver block" << std::endl;
        return false;
      }
    }
    /// End Horrible needed code

    /// Horrible needed code to validate IF use choose a  blocked vehicle
    /// because we didn't implemented the DropDown Menu ( Combo Box )
    if ( jo_["destiny"]["id_veh"] != jo_["destiny"]["id_veh_o"] ) {
      if ( vehicleIsBlocked() ) {
        std::cout << "Vehicle block" << std::endl;
        return false;
      }
    }
    /// End Horrible needed code

    QSqlDatabase::database().transaction();

    if ( not updateDestinations()
      || not updateTravel()
    ) {
      QSqlDatabase::database().rollback();
      return false;
    }

    QSqlDatabase::database().commit();
    return true;
  }

  bool driverIsBlocked() const
  {
    QString sqlStm = "select 1 from drivers where blocked = 1 and id = :id ";

    std::map<QString, QVariant> binds;
    binds.insert(Burden(":id", QVariant(jo_["destiny"]["id_dri"])) );

    return  db_.search(sqlStm, binds).next();
  }

  bool vehicleIsBlocked() const
  {
    QString sqlStm = "select 1 from vehicles where blocked = 1 and id = :id ";

    std::map<QString, QVariant> binds;
    binds.insert(Burden(":id", QVariant(jo_["destiny"]["id_veh"])) );

    return  db_.search(sqlStm, binds).next();
  }

  bool updateDestinations()
  {
    QString sqlStm = "UPDATE destinations "
     "  SET "
     "    id_driver = :id_driver, id_vehicle = :id_vehicle "
     "  , arrival_date = :arrival_date, street = :street   "
     "  , house_nro = :house_nro, post_code = :post_code   "
     "  WHERE id = :id_destination";

    std::map<QString, QVariant>  binds;
    binds.insert(Burden(":id_destination",
          QVariant(jo_["destiny"]["reference"]) ));

    binds.insert(Burden(":id_driver", QVariant(jo_["destiny"]["id_dri"]) ));
    binds.insert(Burden(":id_vehicle",QVariant(jo_["destiny"]["id_veh"]) ));

    binds.insert(Burden(":arrival_date",
          QVariant(jo_["destiny"]["arr_date"]) ));

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
    QString sqlStm = "UPDATE travels "
     "  SET "
     "   id_client = :id_client, sta_date = :sta_date "
     "  WHERE id = :id";

    std::map<QString, QVariant>  binds;
    binds.insert(Burden(":id",        QVariant(jo_["reference"]) ));
    binds.insert(Burden(":id_client", QVariant(jo_["id_cli"]) ));
    binds.insert(Burden(":sta_date",  QVariant(jo_["sta_date"]) ));

    return db_.update(sqlStm, binds);
  }

  UpdateById(const QJsonObject &jo
            ,const QString &id
            ,const controllers::DatabaseController &db)
    : jo_(jo)
     ,id_(id)
     ,db_(db) {}

  UpdateById(const UpdateById&) = delete;
  UpdateById& operator =(const UpdateById&) = delete;

  UpdateById(const UpdateById&&) = delete;
  ~UpdateById() = default;

  const QJsonObject &jo_;
  const QString &id_;
  const controllers::DatabaseController &db_;
};

} //  controllers
} // lg

#endif  // UPDATE_BY_ID_H

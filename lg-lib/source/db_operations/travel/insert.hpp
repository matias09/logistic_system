#ifndef INSERT_H
#define INSERT_H

#include <controllers/databasecontroller.h>
#include <controllers/tracommandcontroller.h>

#include <QJsonObject>

#include <lg-lib_global.h>

#include <iostream>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT TraCommandController::Insert
{
  typedef std::pair<QString, QVariant> Burden;
public:
  static bool call(const QJsonObject &jo
                 , const controllers::DatabaseController &db)
  { return Insert(jo, db).exec(); }

private:
  bool exec() const
  {
    if ( jo_.isEmpty() ) return false;

    QSqlDatabase::database().transaction();

    if (     driverIsBlocked()
      ||     vehicleIsBlocked()
      || not insertTravel()
      || not insertDestinations()
      || not insertDestinationsAssociation()
      || not updateDriverToBlock()
      || not updateVehicleToBlock()
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

  bool insertTravel() const
  {
    QString sqlStm =
      "INSERT INTO travels "
      " ( id_client, sta_date ) "
      " VALUES "
      " ( :id_client, :sta_date )";

    std::map<QString, QVariant> binds;
    binds.insert(Burden(":id_client", QVariant(jo_["id_cli"])) );
    binds.insert(Burden(":sta_date",  QVariant(jo_["sta_date"])) );

    return  db_.create(sqlStm, binds);
  }

  bool insertDestinations() const
  {
    QString sqlStm =
       " INSERT INTO destinations "
       " ( id_driver, id_vehicle, arrival_date "
       " , street, house_nro, post_code) "
       "  VALUES "
       " ( :id_driver, :id_vehicle, :arrival_date "
       " , :street, :house_nro, :post_code) ";

    std::map<QString, QVariant> binds;
    binds.insert(Burden( ":id_driver",  QVariant(jo_["destiny"]["id_dri"]) ));
    binds.insert(Burden( ":id_vehicle", QVariant(jo_["destiny"]["id_veh"]) ));
    binds.insert(Burden( ":arrival_date",
          QVariant(jo_["destiny"]["arr_date"]) ));

    binds.insert(Burden(":street",
          QVariant(jo_["destiny"]["address"]["street"])) );
    binds.insert(Burden(":house_nro",
          QVariant(jo_["destiny"]["address"]["house_nro"]) ));
    binds.insert(Burden(":post_code",
          QVariant(jo_["destiny"]["address"]["postcode"]) ));

    return db_.create(sqlStm, binds);
  }

  bool insertDestinationsAssociation() const
  {
    QString sqlStm =
      "INSERT INTO travels_destinations "
      " ( id_travel, id_destination ) "
      " VALUES "
      " ( :id_travel, :id_destination )";

    std::map<QString, QVariant> binds;
    binds.insert(Burden(":id_travel",
                        QVariant( db_.getTableLastId("travels"))) );
    binds.insert(Burden(":id_destination",
                        QVariant( db_.getTableLastId("destinations"))) );

    return db_.create(sqlStm, binds);
  }

  bool updateDriverToBlock() const
  {
    QString sqlStm = "update drivers set blocked = 1 where  id = :id ";

    std::map<QString, QVariant> binds;
    binds.update(Burden(":id", QVariant(jo_["destiny"]["id_dri"])) );

    return  db_.update(sqlStm, binds);
  }

  bool updateVehicleToBlock() const
  {
    QString sqlStm = "update vehicles set blocked = 1 where  id = :id ";

    std::map<QString, QVariant> binds;
    binds.update(Burden(":id", QVariant(jo_["destiny"]["id_veh"])) );

    return  db_.update(sqlStm, binds);
  }

  Insert(const QJsonObject &jo
        ,const controllers::DatabaseController &db)
    : jo_(jo)
     ,db_(db) {}

  Insert(const Insert&) = delete;
  Insert& operator =(const Insert&) = delete;

  Insert(const Insert&&) = delete;
  ~Insert() = default;

  const QJsonObject &jo_;
  const controllers::DatabaseController &db_;
};

} //  controllers
} // lg

#endif  // INSERT_H

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

    if ( not insertTravel()
      || not insertDestinations()
      || not insertDestinationsAssociation()
   // || not blockDrivers()  FIXME: Add Update
   // || not blockVehicles() FIXME: Add Update
    ) {
      QSqlDatabase::database().rollback();
      return false;
    }

    QSqlDatabase::database().commit();
    //insertDestinationsAssociation();
    return true;
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

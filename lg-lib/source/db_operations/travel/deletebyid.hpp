#ifndef DELETE_BY_ID_H
#define DELETE_BY_ID_H

#include <controllers/databasecontroller.h>
#include <controllers/tracommandcontroller.h>

#include <lg-lib_global.h>

#include <iostream>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT TraCommandController::DeleteById
{
  typedef std::pair<QString, QVariant> Burden;
public:
  static bool call(const QJsonObject &jo
                  ,const QString &id
                  ,const controllers::DatabaseController &db)
  { return DeleteById(jo, db).exec(id); }

private:
  bool exec(const QString &id) {
    if ( jo_.isEmpty() ) return false;

    QSqlDatabase::database().transaction();

    if ( not deleteDestinations(id)
      || not deleteDestinationsAssociation(id)
      || not deleteTravel(id)
      || not unblockDriver()
      || not unblockVehicle()
   ) {
      QSqlDatabase::database().rollback();
      return false;
    }

    QSqlDatabase::database().commit();
    return true;
  }

  bool deleteTravel(const QString &id) const
  {
    QString sqlStm = " DELETE FROM travels WHERE id = :id ";

    std::map<QString, QVariant> binds;
    binds.insert(Burden( ":id", QVariant(id).toInt() ));

    return db_.remove(sqlStm, binds);
  }

  bool deleteDestinationsAssociation(const QString &id) const
  {
    QString sqlStm = "   DELETE FROM travels_destinations "
                      "   WHERE id_travel = :id_t ";

    std::map<QString, QVariant> binds;
    binds.insert(Burden( ":id_t", QVariant(id).toInt() ));

    return db_.remove(sqlStm, binds);
  }

  bool deleteDestinations(const QString &id) const
  {
    QString sqlStm = "DELETE FROM destinations WHERE id IN ( "
                      " ( "
                      "   SELECT id_destination "
                      "     FROM travels_destinations "
                      "    WHERE id_travel = :id_t "
                      " ) "
                    " ) " ;

    std::map<QString, QVariant> binds;
    binds.insert(Burden( ":id_t", QVariant(id).toInt() ));

    return db_.remove(sqlStm, binds);
  }

  bool unblockDriver() const
  {
    QString sqlStm = "UPDATE drivers SET blocked = 0 WHERE  id = :id ";

    std::map<QString, QVariant> binds;
    binds.insert(Burden(":id", QVariant(jo_["destiny"]["id_dri_o"])) );

    return  db_.update(sqlStm, binds);
  }

  bool unblockVehicle() const
  {
    QString sqlStm = "UPDATE vehicles SET blocked = 0 WHERE  id = :id ";

    std::map<QString, QVariant> binds;
    binds.insert(Burden(":id", QVariant(jo_["destiny"]["id_veh_o"])) );

    return  db_.update(sqlStm, binds);
  }

  DeleteById(const QJsonObject &jo
            ,const controllers::DatabaseController &db)
    : jo_(jo)
     ,db_(db) {}
  DeleteById(const DeleteById&) = delete;
  DeleteById& operator =(const DeleteById&) = delete;

  DeleteById(const DeleteById&&) = delete;
  ~DeleteById() = default;

  const QJsonObject &jo_;
  const controllers::DatabaseController &db_;
};

} //  controllers
} // lg

#endif  // DELETE_BY_ID_H

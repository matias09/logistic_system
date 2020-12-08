#ifndef DELETE_BY_ID_H
#define DELETE_BY_ID_H

#include <controllers/databasecontroller.h>
#include <controllers/dricommandcontroller.h>

#include <lg-lib_global.h>

#include <iostream>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT DriCommandController::DeleteById
{
  typedef std::pair<QString, QVariant> Burden;

public:
  static bool call(QString &err,
                   const QString &id
                  ,const controllers::DatabaseController &db)
  { return DeleteById(db).exec(err, id); }

private:
  bool exec(QString &err, const QString &qsid) const
  {
    if ( qsid.isEmpty() ) return false;

    const unsigned int id = qsid.toInt();

    if ( checkIfIsBlocked(id) ) {
      err.append("El chofer no puede ser eliminado, "
                  "actualmente tiene viajes en proceso.");
      return false;
    }

    QSqlDatabase::database().transaction();

    if ( not deleteById(id) ) {
      err.append("El chofer no ha podido ser borrado");

      QSqlDatabase::database().rollback();
      return false;
    }

    QSqlDatabase::database().commit();
    return true;
  }

  bool checkIfIsBlocked(const int id) const
  {
    const short unsigned int blocked = 1;
    QString sqlStm =
        "SELECT 1  "
        " FROM drivers "
        " WHERE id = :id "
        "   AND blocked  = :blocked ";

    std::map<QString, QVariant> binds;
    binds.insert(Burden(":id",       id ));
    binds.insert(Burden(":blocked", blocked ));

    return  (db_.search(sqlStm, binds)).next();
  }

  bool deleteById(const int id) const
  {
    QString sqlStm = "DELETE FROM drivers WHERE id = :id";

    std::map<QString, QVariant> binds;
    binds.insert(Burden(":id", id ));

    return db_.remove(sqlStm, binds);
  }

  const controllers::DatabaseController &db_;

  DeleteById(const controllers::DatabaseController &db) : db_(db) {}
  DeleteById(const DeleteById&) = delete;
  DeleteById& operator =(const DeleteById&) = delete;

  DeleteById(const DeleteById&&) = delete;
  ~DeleteById() = default;
};

} //  controllers
} // lg

#endif  // DELETE_BY_ID_H

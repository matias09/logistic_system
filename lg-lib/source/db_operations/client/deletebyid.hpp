#ifndef DELETE_CLIENT_BY_ID_H
#define DELETE_CLIENT_BY_ID_H

#include <controllers/databasecontroller.h>
#include <controllers/clicommandcontroller.h>

#include <lg-lib_global.h>

#include <iostream>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT CliCommandController::DeleteById
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

    if ( checkForActiveTravels(id) ) {
      err.append("The Client can't be erased, because "
                  "currently has Travels in progress.");
      return false;
    }

    QSqlDatabase::database().transaction();

    if ( not deleteById(id) ) {
      err.append("The Client couldn't be erased.");

      QSqlDatabase::database().rollback();
      return false;
    }

    QSqlDatabase::database().commit();
    return true;
  }

  bool checkForActiveTravels(const int id) const
  {
    const short unsigned int current_active = 0;
    QString sqlStm =
        "SELECT 1  "
        "  FROM clients c "
        " INNER JOIN travels t ON (t.id_client = c.id) "
        " WHERE t.ended        = :ended "
        "   AND t.canceled     = :canceled ";

    std::map<QString, QVariant> binds;
    binds.insert(Burden(":id",       id ));
    binds.insert(Burden(":ended",    current_active ));
    binds.insert(Burden(":canceled", current_active ));

    return  (db_.search(sqlStm, binds)).next();
  }

  bool deleteById(const int id) const
  {
    QString sqlStm = "DELETE FROM clients WHERE id = :id";

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

#endif  // DELETE_CLIENT_BY_ID_H

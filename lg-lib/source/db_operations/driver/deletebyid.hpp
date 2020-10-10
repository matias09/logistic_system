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
public:
  static bool call(const QString &id
                  ,const controllers::DatabaseController &db)
  { return DeleteById().exec(id, db); }

private:
  bool exec(const QString &id
           ,const controllers::DatabaseController &db)
  {
    if ( id.isEmpty() ) return false;

    QString sqlStm = "DELETE FROM drivers WHERE id = :id";

    std::map<QString, QVariant> binds;
    binds.insert(std::pair<QString, QVariant>( ":id", QVariant(id).toInt() ));

    return db.remove(sqlStm, binds);
  }

  DeleteById() = default;
  DeleteById(const DeleteById&) = delete;
  DeleteById& operator =(const DeleteById&) = delete;

  DeleteById(const DeleteById&&) = delete;
  ~DeleteById() = default;
};

} //  controllers
} // lg

#endif  // DELETE_BY_ID_H

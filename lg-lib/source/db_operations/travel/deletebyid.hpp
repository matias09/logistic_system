#ifndef DELETE_BY_ID_H
#define DELETE_BY_ID_H

#include <controllers/databasecontroller.h>
#include <controllers/tracommandcontroller.h>

#include <lg-lib_global.h>

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

    if ( not cancelTravel(id)
      || not unblockDriver()
      || not unblockVehicle()
   ) {
      QSqlDatabase::database().rollback();
      return false;
    }

    QSqlDatabase::database().commit();
    return true;
  }

  bool cancelTravel(const QString &id) const
  {
    const unsigned int ended = 1;
    QString sqlStm = "UPDATE travels SET canceled = :canceled WHERE id = :id";

    std::map<QString, QVariant> binds;
    binds.insert(Burden( ":id",       QVariant(id).toInt() ));
    binds.insert(Burden( ":canceled", ended ));

    return db_.remove(sqlStm, binds);
  }

  bool unblockDriver() const
  {
    const unsigned int blocked = 0;
    QString sqlStm = "UPDATE drivers SET blocked = :blocked WHERE  id = :id ";

    std::map<QString, QVariant> binds;
    binds.insert(Burden(":id", QVariant(jo_["destiny"]["id_dri"].toInt())) );
    binds.insert(Burden(":blocked", blocked) );

    return  db_.update(sqlStm, binds);
  }

  bool unblockVehicle() const
  {
    const unsigned int blocked = 0;
    QString sqlStm = "UPDATE vehicles SET blocked = :blocked WHERE  id = :id ";

    std::map<QString, QVariant> binds;
    binds.insert(Burden(":id", QVariant(jo_["destiny"]["id_veh"].toInt())) );
    binds.insert(Burden(":blocked", blocked) );

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

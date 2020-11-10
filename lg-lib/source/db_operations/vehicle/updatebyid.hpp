#ifndef UPDATE_VEHICLE_BY_ID_H
#define UPDATE_VEHICLE_BY_ID_H

#include <controllers/databasecontroller.h>
#include <controllers/vehcommandcontroller.h>

#include <QJsonObject>

#include <lg-lib_global.h>

#include <iostream>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT VehCommandController::UpdateById
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

    QString sqlStm = "                                          \
       UPDATE vehicles                                          \
       SET  id_type_vehicle = :id_type, id_model = :id_model    \
          , max_weight = :max_w, vin = :vin                     \
          , vin_cad_date = :vin_cad, year = :year               \
       WHERE id = :id ";

    std::map<QString, QVariant> binds;
    binds.insert(Burden(":id_model",  QVariant(jo["id_model"].toInt())) );
    binds.insert(Burden(":id_type",   QVariant(jo["id_type"].toInt())) );

    binds.insert(Burden(":id",         QVariant(jo["reference"])) );
    binds.insert(Burden(":max_w",      QVariant(jo["max_w"])) );
    binds.insert(Burden(":vin",        QVariant(jo["vin"])) );
    binds.insert(Burden(":vin_cad",    QVariant(jo["vin_cad"])) );
    binds.insert(Burden(":year",       QVariant(jo["year"])) );

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

#endif  // UPDATE_VEHICLE_BY_ID_H

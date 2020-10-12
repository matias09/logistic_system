#ifndef INSERT_VEHICLE_H
#define INSERT_VEHICLE_H

#include <controllers/databasecontroller.h>
#include <controllers/vehcommandcontroller.h>

#include <QJsonObject>

#include <lg-lib_global.h>

#include <iostream>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT VehCommandController::Insert
{
  typedef std::pair<QString, QVariant> Burden;
public:
  static bool call(const QJsonObject &jo
                  ,const controllers::DatabaseController &db)
  { return Insert().exec(jo, db); }

private:
  bool exec(const QJsonObject &jo
           ,const controllers::DatabaseController &db)
  {
    if ( jo.isEmpty() ) return false;

    QString sqlStm = "                                                      \
      INSERT INTO vehicles                                                  \
      ( id_type_vehicle, id_model, max_weight, vin, vin_cad_date, year)     \
       VALUES                                                               \
      ( :type, :model, :max_w, :vin, :vin_cad, :year) ";

    std::map<QString, QVariant> binds;
    binds.insert(Burden(":model",      QVariant(jo["model"])) );
    binds.insert(Burden(":type",       QVariant(jo["type"])) );
    binds.insert(Burden(":reference",  QVariant(jo["reference"])) );
    binds.insert(Burden(":max_w",      QVariant(jo["max_w"])) );
    binds.insert(Burden(":vin",        QVariant(jo["vin"])) );
    binds.insert(Burden(":vin_cad",    QVariant(jo["vin_cad"])) );
    binds.insert(Burden(":year",       QVariant(jo["year"])) );

    return  db.create(sqlStm, binds);
  }

  Insert() = default;
  Insert(const Insert&) = delete;
  Insert& operator =(const Insert&) = delete;

  Insert(const Insert&&) = delete;
  ~Insert() = default;
};

} //  controllers
} // lg

#endif  // INSERT_VEHICLE_H

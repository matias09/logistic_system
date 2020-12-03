#ifndef GET_OPT_UNBLOCKED_H
#define GET_OPT_UNBLOCKED_H

#include <controllers/databasecontroller.h>
#include <controllers/tracommandcontroller.h>
#include <data/combooption.h>

#include <QList>
#include <QDateTime>

#include <lg-lib_global.h>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT TraCommandController::GetOptVehicle
{
public:
  static QList<data::ComboOption*> call(
      QObject &parent
     ,const controllers::DatabaseController &db)
  { return GetOptVehicle().exec(parent, db); }

private:
  QList<data::ComboOption*> exec(
      QObject &parent
     ,const controllers::DatabaseController &db)
  {
    const unsigned int unblock_value = 0;

    QString sqlStm = "SELECT id, name             "
                     "  FROM  vehicles "
                     " WHERE blocked = :blocked "
                     "   AND vin_cad_date > :current_date ";

    std::map<QString, QVariant> binds {
      std::pair<QString, QVariant>( ":blocked", unblock_value)
     ,std::pair<QString, QVariant>( ":current_date", QDateTime::currentDateTime())
    };

    QSqlQuery&& query = db.search(sqlStm, binds);

    QList<data::ComboOption*> cl{};
    while ( query.next() ) {
      data::ComboOption* co = new data::ComboOption(
        &parent
       ,query.value(0).toString()
       ,query.value(1).toString() );

      cl.append(co);
    }

    return cl;
  }

  GetOptVehicle() = default;
  GetOptVehicle(const GetOptVehicle&) = delete;
  GetOptVehicle& operator =(const GetOptVehicle&) = delete;

  GetOptVehicle(const GetOptVehicle&&) = delete;
  ~GetOptVehicle() = default;
};

} // controller
} // lg

#endif  // GET_OPT_UNBLOCKED_H

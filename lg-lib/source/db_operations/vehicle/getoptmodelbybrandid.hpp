#ifndef GET_OPT_MODEL_BY_BRAND_ID_H
#define GET_OPT_MODEL_BY_BRAND_ID_H

#include <controllers/databasecontroller.h>
#include <controllers/vehcommandcontroller.h>
#include <data/combooption.h>

#include <QList>

#include <lg-lib_global.h>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT VehCommandController::GetOptModelByBrandId
{
public:
  static QList<data::ComboOption*> call(
      int id
     ,QObject &parent
     ,const controllers::DatabaseController &db)
  { return GetOptModelByBrandId().exec(id, parent, db); }

private:
  QList<data::ComboOption*> exec(
      int id
     ,QObject &parent
     ,const controllers::DatabaseController &db)
  {
    QString sqlStm = "SELECT id, name             "
                     "  FROM models               "
                     " WHERE id_brand = :id_brand ";

    std::map<QString, QVariant> binds {
      std::pair<QString, QVariant>( ":id_brand", QVariant(id) )
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

  GetOptModelByBrandId() = default;
  GetOptModelByBrandId(const GetOptModelByBrandId&) = delete;
  GetOptModelByBrandId& operator =(const GetOptModelByBrandId&) = delete;

  GetOptModelByBrandId(const GetOptModelByBrandId&&) = delete;
  ~GetOptModelByBrandId() = default;
};

} // controller
} // lg

#endif  // GET_OPT_MODEL_BY_BRAND_ID_H

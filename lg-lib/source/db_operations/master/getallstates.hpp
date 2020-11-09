#ifndef GET_ALL_STATES_H
#define GET_ALL_STATES_H

#include <controllers/databasecontroller.h>
#include <controllers/mastercontroller.h>
#include <data/combooption.h>

#include <QJsonObject>
#include <QList>

#include <lg-lib_global.h>

#include <iostream>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT MasterController::GetAllStates
{
public:
  static QList<data::ComboOption*> call(
      QObject &parent
     ,const controllers::DatabaseController &db)
  { return GetAllStates().exec(parent, db); }

private:
  QList<data::ComboOption*> exec(
      QObject &parent
     ,const controllers::DatabaseController &db)
  {
    QString sqlStm = "SELECT id, name FROM states";

    QSqlQuery&& query = db.search(sqlStm, {});

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

  GetAllStates() = default;
  GetAllStates(const GetAllStates&) = delete;
  GetAllStates& operator =(const GetAllStates&) = delete;

  GetAllStates(const GetAllStates&&) = delete;
  ~GetAllStates() = default;
};

} //  controllers {
} // lg

#endif  // GET_ALL_STATES_H

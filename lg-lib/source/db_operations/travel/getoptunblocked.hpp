#ifndef GET_OPT_UNBLOCKED_H
#define GET_OPT_UNBLOCKED_H

#include <controllers/databasecontroller.h>
#include <controllers/tracommandcontroller.h>
#include <data/combooption.h>

#include <QList>

#include <lg-lib_global.h>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT TraCommandController::GetOptUnblocked
{
public:
  static QList<data::ComboOption*> call(
      const QString &table
     ,QObject &parent
     ,const controllers::DatabaseController &db)
  { return GetOptUnblocked().exec(table, parent, db); }

private:
  QList<data::ComboOption*> exec(
      const QString &table
     ,QObject &parent
     ,const controllers::DatabaseController &db)
  {
    const unsigned int unblock_value = 0;

    QString sqlStm = "SELECT id, name             "
                     "  FROM  " + table +
                     " WHERE blocked = :blocked ";

    std::map<QString, QVariant> binds {
      std::pair<QString, QVariant>( ":blocked", unblock_value)
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

  GetOptUnblocked() = default;
  GetOptUnblocked(const GetOptUnblocked&) = delete;
  GetOptUnblocked& operator =(const GetOptUnblocked&) = delete;

  GetOptUnblocked(const GetOptUnblocked&&) = delete;
  ~GetOptUnblocked() = default;
};

} // controller
} // lg

#endif  // GET_OPT_UNBLOCKED_H

#ifndef GET_OPTION_FROM_TABLE_H
#define GET_OPTION_FROM_TABLE_H

#include <controllers/databasecontroller.h>
#include <data/combooption.h>

#include <QList>

#include <lg-lib_global.h>

namespace lg {
namespace controllers {

class LGLIBSHARED_EXPORT GetOptionFromTable
{
public:
  static QList<lg::data::ComboOption*> call(
      const QString &table
     ,QObject &parent
     ,const controllers::DatabaseController &db)
  { return GetOptionFromTable().exec(table, parent, db); }

private:
  QList<lg::data::ComboOption*> exec(
      const QString &table
     ,QObject &parent
     ,const controllers::DatabaseController &db)
  {
    QString sqlStm = "SELECT id, name FROM " + table;

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

  GetOptionFromTable() = default;
  GetOptionFromTable(const GetOptionFromTable&) = delete;
  GetOptionFromTable& operator =(const GetOptionFromTable&) = delete;

  GetOptionFromTable(const GetOptionFromTable&&) = delete;
  ~GetOptionFromTable() = default;
};

} // lg
} // lg

#endif  // GET_OPTION_FROM_TABLE_H

#ifndef DRIVERSEARCH_H
#define DRIVERSEARCH_H

#include <QScopedPointer>

#include <lg-lib_global.h>
#include <controllers/databasecontroller.h>
#include <data/stringdecorator.h>
#include <data/entity.h>
#include <data/entitycollection.h>
#include <models/driver.h>

namespace lg {
namespace models {

class LGLIBSHARED_EXPORT DriverSearch : public data::Entity
{
  Q_OBJECT
  Q_PROPERTY( lg::data::StringDecorator *ui_searchText READ
              searchText CONSTANT )
  Q_PROPERTY( QQmlListProperty<lg::models::Driver> ui_searchResults READ
              ui_searchResults NOTIFY searchResultsChanged )

public:
  DriverSearch(QObject *parent = nullptr,
               controllers::DatabaseController *databaseController = nullptr);

  ~DriverSearch();

  data::StringDecorator *searchText();
  QQmlListProperty<Driver> ui_searchResults();
  void search();

signals:
  void searchResultsChanged();

private:
  class Implementation;
  QScopedPointer<Implementation> implementation;

  class FindByName;
};

}
}

#endif //  DRIVERSEARCH_H

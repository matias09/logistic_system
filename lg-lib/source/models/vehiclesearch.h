#ifndef VEHICLESEARCH_H
#define VEHICLESEARCH_H

#include <QScopedPointer>

#include <lg-lib_global.h>
#include <controllers/databasecontroller.h>
#include <data/stringdecorator.h>
#include <data/entity.h>
#include <data/entitycollection.h>
#include <models/vehicle.h>

namespace lg {
namespace models {

class LGLIBSHARED_EXPORT VehicleSearch : public data::Entity
{
  Q_OBJECT
  Q_PROPERTY( lg::data::StringDecorator *ui_searchText READ
              searchText CONSTANT )
  Q_PROPERTY( QQmlListProperty<lg::models::Vehicle> ui_searchResults READ
              ui_searchResults NOTIFY searchResultsChanged )

public:
  VehicleSearch(QObject *parent = nullptr,
               controllers::DatabaseController *databaseController = nullptr);

  ~VehicleSearch();

  data::StringDecorator *searchText();
  QQmlListProperty<Vehicle> ui_searchResults();
  void search();

signals:
  void searchResultsChanged();

private:
  class Implementation;
  QScopedPointer<Implementation> implementation;

  class FindByBrand;
};

}
}

#endif //  VEHICLESEARCH_H

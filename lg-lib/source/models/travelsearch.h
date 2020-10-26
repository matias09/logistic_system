#ifndef TRAVELSEARCH_H
#define TRAVELSEARCH_H

#include <QScopedPointer>
#include <QtQml/QQmlListProperty>

#include <lg-lib_global.h>
#include <controllers/databasecontroller.h>

#include <data/stringdecorator.h>
#include <data/entity.h>
#include <data/entitycollection.h>

#include <models/travel.h>

namespace lg {
namespace models {

class LGLIBSHARED_EXPORT TravelSearch : public data::Entity
{
  Q_OBJECT
  Q_PROPERTY( lg::data::StringDecorator *ui_searchText READ
              searchText CONSTANT )
  Q_PROPERTY( QQmlListProperty<lg::models::Travel> ui_searchResults READ
              ui_searchResults NOTIFY searchResultsChanged )

public:
  TravelSearch(QObject *parent = nullptr,
               controllers::DatabaseController *databaseController = nullptr);

  ~TravelSearch();

  data::StringDecorator *searchText();
  QQmlListProperty<Travel> ui_searchResults();
  void search();

signals:
  void searchResultsChanged();

private:
  class Implementation;
  QScopedPointer<Implementation> implementation;

  class FindByClientName;
};

}
}

#endif //  TRAVELSEARCH_H

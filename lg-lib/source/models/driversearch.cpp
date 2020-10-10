#include "driversearch.h"
#include "db_operations/driver/findbyname.hpp"

#include <iostream>

using namespace lg::controllers;
using namespace lg::data;

namespace lg {
namespace models {

class DriverSearch::Implementation
{
public:
  Implementation( DriverSearch *_driverSearch
                 ,DatabaseController *_databaseController )
    : driverSearch( _driverSearch )
    , databaseController( _databaseController ) {}

    DriverSearch *driverSearch{nullptr};
    DatabaseController    *databaseController{nullptr};
    data::StringDecorator *searchText{nullptr};
    data::EntityCollection<Driver> *searchResults{nullptr};
};

DriverSearch::DriverSearch( QObject *parent
                          ,DatabaseController *databaseController )
     : Entity( parent, "DriverSearch")
{
  implementation.reset( new Implementation(this, databaseController) );
  implementation->searchText = static_cast<StringDecorator*>(
      addDataItem( new StringDecorator(this, "searchText", "Buscar") )
  );
  implementation->searchResults = static_cast<EntityCollection<Driver>* >(
    addChildCollection( new EntityCollection<Driver>(this, "searchResults") )
  );

  connect( implementation->searchResults
         , &EntityCollection<Driver>::collectionChanged
         , this
         , &DriverSearch::searchResultsChanged );
}

DriverSearch::~DriverSearch(){}

StringDecorator* DriverSearch::searchText()
{
  return implementation->searchText;
}

QQmlListProperty<Driver> DriverSearch::ui_searchResults()
{
  return QQmlListProperty<Driver>(
    this,
    implementation->searchResults->derivedEntities() );
}

void DriverSearch::search()
{
  std::cout << "Search for "
            <<  implementation->searchText->value().toStdString()
            << "..." << std::endl;

  QJsonArray resultsArray;
  FindByName::call(resultsArray
                  ,implementation->searchText->value()
                  ,*(implementation->databaseController));

  implementation->searchResults->update( resultsArray );

  emit searchResultsChanged();

  std::cout << "Found  "
            <<  implementation->searchResults->baseEntities().size()
            << " matches." << std::endl;
}

} // models
} // lg

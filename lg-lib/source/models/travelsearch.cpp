#include "travelsearch.h"
#include "db_operations/travel/findbyname.hpp"

#include <iostream>

using namespace lg::controllers;
using namespace lg::data;

namespace lg {
namespace models {

class TravelSearch::Implementation
{
public:
  Implementation( TravelSearch       *_travelSearch
                 ,DatabaseController *_databaseController )
    : travelSearch( _travelSearch )
    , databaseController( _databaseController ) {}

    TravelSearch          *travelSearch{nullptr};
    DatabaseController    *databaseController{nullptr};
    data::StringDecorator *searchText{nullptr};
    data::EntityCollection<Travel> *searchResults{nullptr};
};

TravelSearch::TravelSearch( QObject *parent
                          ,DatabaseController *databaseController )
     : Entity( parent, "TravelSearch")
{
  implementation.reset( new Implementation(this, databaseController) );
  implementation->searchText = static_cast<StringDecorator*>(
      addDataItem( new StringDecorator(this, "searchText", "Buscar") )
  );
  implementation->searchResults = static_cast<EntityCollection<Travel>* >(
    addChildCollection( new EntityCollection<Travel>(this, "searchResults") )
  );

  connect( implementation->searchResults
         , &EntityCollection<Travel>::collectionChanged
         , this
         , &TravelSearch::searchResultsChanged );
}

TravelSearch::~TravelSearch(){}

StringDecorator* TravelSearch::searchText()
{
  return implementation->searchText;
}

QQmlListProperty<Travel> TravelSearch::ui_searchResults()
{
  return QQmlListProperty<Travel>(
    this,
    implementation->searchResults->derivedEntities() );
}

void TravelSearch::search()
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

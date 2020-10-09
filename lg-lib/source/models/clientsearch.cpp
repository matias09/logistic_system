#include "clientsearch.h"
#include "db_operations/client/findbyname.hpp"

#include <iostream>

using namespace lg::controllers;
using namespace lg::data;

namespace lg {
namespace models {

class ClientSearch::Implementation
{
public:
  Implementation( ClientSearch *_clientSearch
                 ,DatabaseController  *_databaseController )
    : clientSearch( _clientSearch )
    , databaseController( _databaseController ) {}

    ClientSearch *clientSearch{nullptr};
    DatabaseController    *databaseController{nullptr};
    data::StringDecorator *searchText{nullptr};
    data::EntityCollection<Client> *searchResults{nullptr};
};

ClientSearch::ClientSearch( QObject *parent
                          ,DatabaseController *databaseController )
     : Entity( parent, "ClientSearch")
{
  implementation.reset( new Implementation(this, databaseController) );
  implementation->searchText = static_cast<StringDecorator*>(
      addDataItem( new StringDecorator(this, "searchText", "Buscar") )
  );
  implementation->searchResults = static_cast<EntityCollection<Client>* >(
    addChildCollection( new EntityCollection<Client>(this, "searchResults") )
  );

  connect( implementation->searchResults
         , &EntityCollection<Client>::collectionChanged
         , this
         , &ClientSearch::searchResultsChanged );
}

ClientSearch::~ClientSearch(){}

StringDecorator* ClientSearch::searchText()
{
  return implementation->searchText;
}

QQmlListProperty<Client> ClientSearch::ui_searchResults()
{
  return QQmlListProperty<Client>(
    this,
    implementation->searchResults->derivedEntities() );
}

void ClientSearch::search()
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

#include "clientsearch.h"

#include <iostream>

using namespace lg::controllers;
using namespace lg::data;

namespace lg {
namespace models {

class ClientSearch::Implementation
{
public:
  Implementation( ClientSearch *_clientSearch
                 ,IDatabaseController *_databaseController )
    : clientSearch( _clientSearch )
    , databaseController( _databaseController ) {}

    ClientSearch *clientSearch{nullptr};
    IDatabaseController *databaseController{nullptr};
    data::StringDecorator *searchText{nullptr};
    data::EntityCollection<Client> *searchResults{nullptr};
};

ClientSearch::ClientSearch( QObject *parent
                          ,IDatabaseController *databaseController )
     : Entity( parent, "ClientSearch")
{
  implementation.reset( new Implementation(this, databaseController) );
  implementation->searchText = static_cast<StringDecorator*>(
      addDataItem( new StringDecorator(this, "searchText", "Search Text") )
  );
  implementation->searchResults = static_cast<EntityCollection<Client>* >(
    addChildCollection( new EntityCollection<Client>(this, "searchResults") )
  );


  //TODO: Fix this, Is not working as they should.
  // Check again the Entities explanation from the PDF
  // where you copied.
  //
  // This is working only when the find view results
  // are > 0 , If not, Is not clearing the results list
  // with no data. Remains the last search and with
  // an inconsisten state.
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

  auto resultsArray = implementation->databaseController->find(
    "client",
    implementation->searchText->value() );

  implementation->searchResults->update( resultsArray );

  //TODO: Undo this call, and what happen.
  // This call is a BAD Fix for clear the Client Find list
  // when there is NO results to Show.
  emit searchResultsChanged();

  std::cout << "Found  "
            <<  implementation->searchResults->baseEntities().size()
            << " matches." << std::endl;
}

} // models
} // lg

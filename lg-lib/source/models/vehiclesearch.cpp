#include "vehiclesearch.h"
#include "db_operations/vehicle/findbybrand.hpp"

using namespace lg::controllers;
using namespace lg::data;

namespace lg {
namespace models {

class VehicleSearch::Implementation
{
public:
  Implementation( VehicleSearch *_vehicleSearch
                 ,DatabaseController  *_databaseController )
    : vehicleSearch( _vehicleSearch )
    , databaseController( _databaseController ) {}

    VehicleSearch *vehicleSearch{nullptr};
    DatabaseController    *databaseController{nullptr};
    data::StringDecorator *searchText{nullptr};
    data::EntityCollection<Vehicle> *searchResults{nullptr};
};

VehicleSearch::VehicleSearch( QObject *parent
                          ,DatabaseController *databaseController )
     : Entity( parent, "VehicleSearch")
{
  implementation.reset( new Implementation(this, databaseController) );
  implementation->searchText = static_cast<StringDecorator*>(
      addDataItem( new StringDecorator(this, "searchText", "Buscar") )
  );
  implementation->searchResults = static_cast<EntityCollection<Vehicle>* >(
    addChildCollection( new EntityCollection<Vehicle>(this, "searchResults") )
  );

  connect( implementation->searchResults
         , &EntityCollection<Vehicle>::collectionChanged
         , this
         , &VehicleSearch::searchResultsChanged );
}

VehicleSearch::~VehicleSearch(){}

StringDecorator* VehicleSearch::searchText()
{
  return implementation->searchText;
}

QQmlListProperty<Vehicle> VehicleSearch::ui_searchResults()
{
  return QQmlListProperty<Vehicle>(
    this,
    implementation->searchResults->derivedEntities() );
}

void VehicleSearch::search()
{
  QJsonArray resultsArray;
  FindByBrand::call(resultsArray
                  ,implementation->searchText->value()
                  ,*(implementation->databaseController));

  implementation->searchResults->update( resultsArray );

  emit searchResultsChanged();
}

} // models
} // lg

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <controllers/mastercontroller.h>
#include <controllers/navigationcontroller.h>
#include <controllers/clicommandcontroller.h>
#include <controllers/dricommandcontroller.h>
#include <controllers/vehcommandcontroller.h>
#include <controllers/tracommandcontroller.h>

#include <framework/command.h>

#include <data/datetimedecorator.h>
#include <data/intdecorator.h>
#include <data/stringdecorator.h>
#include <data/combooption.h>

#include <models/address.h>
#include <models/destination.h>

#include <models/client.h>
#include <models/clientsearch.h>
#include <models/driver.h>
#include <models/driversearch.h>
#include <models/vehicle.h>
#include <models/vehiclesearch.h>
#include <models/travel.h>
#include <models/travelsearch.h>

int main(int argc, char *argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);
  qmlRegisterType<lg::controllers::MasterController>("LG", 1,  0,  "MasterController");
  qmlRegisterType<lg::controllers::NavigationController>("LG", 1,  0,  "NavigationController");
  qmlRegisterType<lg::controllers::CliCommandController>("LG", 1,  0,  "CliCommandController");
  qmlRegisterType<lg::controllers::DriCommandController>("LG", 1,  0,  "DriCommandController");
  qmlRegisterType<lg::controllers::VehCommandController>("LG", 1,  0,  "VehCommandController");
  qmlRegisterType<lg::controllers::TraCommandController>("LG", 1,  0,  "TraCommandController");

  qmlRegisterType<lg::framework::Command>("LG", 1,  0,  "Command");

  qmlRegisterType<lg::data::DateTimeDecorator>("LG" , 1, 0, "DateTimeDecorator");
  qmlRegisterType<lg::data::IntDecorator>("LG" , 1, 0, "IntDecorator");
  qmlRegisterType<lg::data::StringDecorator>("LG" , 1, 0, "StringDecorator");
  qmlRegisterType<lg::data::ComboOption>("LG", 1, 0, "ComboOption");

  qmlRegisterType<lg::models::Address>("LG", 1, 0, "Address");
  qmlRegisterType<lg::models::Destination>("LG", 1, 0, "Destination");

  qmlRegisterType<lg::models::Client>("LG", 1, 0, "Client");
  qmlRegisterType<lg::models::ClientSearch>("LG", 1, 0, "ClientSearch");

  qmlRegisterType<lg::models::Driver>("LG", 1, 0, "Driver");
  qmlRegisterType<lg::models::DriverSearch>("LG", 1, 0, "DriverSearch");

  qmlRegisterType<lg::models::Vehicle>("LG", 1, 0, "Vehicle");
  qmlRegisterType<lg::models::VehicleSearch>("LG", 1, 0, "VehicleSearch");

  qmlRegisterType<lg::models::Travel>("LG", 1, 0, "Travel");
  qmlRegisterType<lg::models::TravelSearch>("LG", 1, 0, "TravelSearch");

  lg::controllers::MasterController masterController;
  QQmlApplicationEngine engine;

  engine.rootContext()->setContextProperty("masterController", &masterController);
  engine.addImportPath("qrc:/");

  const QUrl url(QStringLiteral("qrc:/views/MasterView.qml"));

  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                   &app, [url](QObject *obj, const QUrl &objUrl) {
    if (!obj && url == objUrl)
      QCoreApplication::exit(-1);
  }, Qt::QueuedConnection);

  engine.load(url);

  return app.exec();
}

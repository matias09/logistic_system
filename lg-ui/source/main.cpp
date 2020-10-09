#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <controllers/mastercontroller.h>
#include <controllers/navigationcontroller.h>
#include <controllers/clicommandcontroller.h>
#include <controllers/dricommandcontroller.h>

#include <framework/command.h>

#include <data/datetimedecorator.h>
#include <data/intdecorator.h>
#include <data/stringdecorator.h>

#include <models/address.h>
#include <models/appointment.h>
#include <models/client.h>
#include <models/clientsearch.h>
#include <models/driver.h>
#include <models/driversearch.h>

int main(int argc, char *argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);
  qmlRegisterType<lg::controllers::MasterController>("LG", 1,  0,  "MasterController");
  qmlRegisterType<lg::controllers::NavigationController>("LG", 1,  0,  "NavigationController");
  qmlRegisterType<lg::controllers::CliCommandController>("LG", 1,  0,  "CliCommandController");
  qmlRegisterType<lg::controllers::DriCommandController>("LG", 1,  0,  "DriCommandController");

  qmlRegisterType<lg::framework::Command>("LG", 1,  0,  "Command");

  qmlRegisterType<lg::data::DateTimeDecorator>("LG" , 1, 0, "DateTimeDecorator");
  qmlRegisterType<lg::data::IntDecorator>("LG" , 1, 0, "IntDecorator");
  qmlRegisterType<lg::data::StringDecorator>("LG" , 1, 0, "StringDecorator");

  qmlRegisterType<lg::models::Address>("LG", 1, 0, "Address");
  qmlRegisterType<lg::models::Appointment>("LG", 1, 0, "Appointment");

  qmlRegisterType<lg::models::Client>("LG", 1, 0, "Client");
  qmlRegisterType<lg::models::ClientSearch>("LG", 1, 0, "ClientSearch");

  qmlRegisterType<lg::models::Driver>("LG", 1, 0, "Driver");
  qmlRegisterType<lg::models::DriverSearch>("LG", 1, 0, "DriverSearch");

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

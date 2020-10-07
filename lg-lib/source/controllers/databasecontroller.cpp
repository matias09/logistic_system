#include "databasecontroller.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QJsonDocument>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QSqlError>

// C++
#include <iostream>

const QString DATABASE_SCHEMA_FILE = "db_schema.sql";
const QString DATABASE_NAME = "lg.sqlite";

namespace lg {
namespace controllers {

class DatabaseController::Implementation
{
public:
  Implementation(DatabaseController *_databaseController)
    : databaseController(_databaseController)
  {
    database = QSqlDatabase::addDatabase("QSQLITE", "lg");
    database.setDatabaseName( DATABASE_NAME );

    if (not initialise())  {
      return;
    }

    std::cout << "Database Sqlite Open " << std::endl;
  }

  DatabaseController *databaseController{nullptr};
  QSqlDatabase database;

private:
  bool initialise()
  {
    QString db_file_path = QDir::currentPath();
    db_file_path.append( QDir::separator() );
    db_file_path += DATABASE_NAME;

    if ( not QFile::exists(db_file_path) ) {
      database.open();

      if ( not createTables() ) {
        std::cout << "ERROR: Unable to Create Database Tables" << std::endl;
        return false;
      }
    } else {
       database.open();
    }

    return true;
  }

  bool createTables()
  {
    bool r = true;

    std::cout << "Creating Database and Tables" << std::endl;

    QFile f (QDir::currentPath() + "/" + DATABASE_SCHEMA_FILE);
    f.open(QIODevice::ReadOnly | QIODevice::Text);

    QString q = f.readAll().trimmed();

    QStringList ql = q.split(";", QString::SkipEmptyParts);

    QSqlQuery query(database);

    foreach( const QString &s, ql)
    {
      query.exec(s);
      if ( query.lastError().type() != QSqlError::NoError ) {
        std::cout << "Can't execute sql file: "
                  << query.lastError().text().toStdString() << std::endl;
        r = false;
        break;
      }
    }
    f.close();

    std::cout << "Query for tables executed" << std::endl;

    return r;
  }
};

DatabaseController::DatabaseController(QObject *parent) : IDatabaseController(parent)
{
  implementation.reset( new Implementation(this) );
}

DatabaseController::~DatabaseController() {}

bool DatabaseController::createClient(const QString &id
                                     ,const QJsonObject &jsonObject) const
{
  if ( id.isEmpty() ) return false;
  if ( jsonObject.isEmpty() ) return false;

  QSqlQuery query(implementation->database);
  QString sqlStatement = "INSERT INTO clients "
       " (name, phone, cellphone, mail , street, city, post_code) "
       "  VALUES "
       " (:name, :phone, :cellphone, :mail, :street, :city, :post_code)";

  query.prepare(sqlStatement);
  if ( query.lastError().type() != QSqlError::NoError ) {
    std::cout << "Can't Prepare sql file: "
              << query.lastError().text().toStdString() << std::endl;
    return false;
  }

  query.bindValue(":name",        QVariant(jsonObject["name"]) );
  query.bindValue(":phone",       QVariant(jsonObject["phone"]) );
  query.bindValue(":cellphone",   QVariant(jsonObject["cellphone"]) );
  query.bindValue(":mail",        QVariant(jsonObject["mail"]) );
  query.bindValue(":street",      QVariant(jsonObject["address"]["street"]) );
  query.bindValue(":city",        QVariant(jsonObject["address"]["city"]) );
  query.bindValue(":post_code",   QVariant(jsonObject["address"]["postcode"]) );

  query.exec();
  if ( query.lastError().type() != QSqlError::NoError ) {
    std::cout << "Can't Execute sql file: "
              << query.lastError().text().toStdString() << std::endl;
    return false;
  }

  return query.numRowsAffected() > 0;
}

bool DatabaseController::deleteClient(const QString &id) const
{
  if ( id.isEmpty() ) return false;

  QSqlQuery query(implementation->database);
  QString sqlStatement = "DELETE FROM clients WHERE id = :id";

  if ( ! query.prepare(sqlStatement) ) return false;

  query.bindValue(":id", id.toInt());

  if ( ! query.exec() ) return false;

  return query.numRowsAffected() > 0;
}

QJsonArray DatabaseController::findClientByName(const QString &searchText) const
{
  if ( searchText.isEmpty() ) return {};

  QSqlQuery query(implementation->database);
  QString sqlStatement = "SELECT id, name, phone, cellphone, mail, street, "
                             " city, post_code "
                         "  FROM clients "
                         " WHERE LOWER(name) LIKE :searchText" ;

  if ( ! query.prepare(sqlStatement) ) return {};

  query.bindValue(":searchText", QVariant("%" + searchText.toLower() + "%") );

  if ( ! query.exec() ) return {};

  QJsonArray returnValue;

  while ( query.next() ) {
    QJsonObject jsonObj;

    jsonObj.insert("reference",        query.value(0).toString() );
    jsonObj.insert("name",      query.value(1).toString() );
    jsonObj.insert("phone",     query.value(2).toString() );
    jsonObj.insert("cellphone", query.value(3).toString() );
    jsonObj.insert("mail",      query.value(4).toString() );

    QJsonObject jsonObjAddress;
    jsonObjAddress.insert("street",    query.value(5).toString() );
    jsonObjAddress.insert("city",      query.value(6).toString() );
    jsonObjAddress.insert("postcode", query.value(7).toString() );

    jsonObj.insert("address",      jsonObjAddress );

    //QJsonDocument doc(jsonObj);
    // std::cout << "Json created : \n" << doc.toJson().toStdString() << std::endl;

    // TODO: Check for jsonObj sanity
    returnValue.append( jsonObj );
  }

  return returnValue;
}

bool DatabaseController::updateClient(const QString &id
                                     ,const QJsonObject &jsonObject) const
{
  if ( id.isEmpty() ) return false;
  if ( jsonObject.isEmpty() ) return false;

  QSqlQuery query(implementation->database);
  QString sqlStatement = "UPDATE clients "
     "  SET "
     "   name = :name, phone = :phone, cellphone = :cellphone "
     " , mail = :mail, street = :street, city = :city, post_code = :post_code "
     "  WHERE id = :id";

  query.prepare(sqlStatement);
  if ( query.lastError().type() != QSqlError::NoError ) {
    std::cout << "Can't Prepare sql file: "
              << query.lastError().text().toStdString() << std::endl;
    return false;
  }

  query.bindValue(":id",          QVariant(id.toInt()) );
  query.bindValue(":name",        QVariant(jsonObject["name"]) );
  query.bindValue(":phone",       QVariant(jsonObject["phone"]) );
  query.bindValue(":cellphone",   QVariant(jsonObject["cellphone"]) );
  query.bindValue(":mail",        QVariant(jsonObject["mail"]) );
  query.bindValue(":street",      QVariant(jsonObject["address"]["street"]) );
  query.bindValue(":city",        QVariant(jsonObject["address"]["city"]) );
  query.bindValue(":post_code",   QVariant(jsonObject["address"]["postcode"]) );

  query.exec();
  if ( query.lastError().type() != QSqlError::NoError ) {
    std::cout << "Can't Execute sql file: "
              << query.lastError().text().toStdString() << std::endl;
    return false;
  }

  return query.numRowsAffected() > 0;
 }

} //  controllers
} // lg

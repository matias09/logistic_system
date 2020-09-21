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

bool DatabaseController::createRow(const QString &tableName
                                  ,const QString &id
                                  ,const QJsonObject &jsonObject) const
{
  if ( tableName.isEmpty() ) return false;
  if ( id.isEmpty() ) return false;
  if ( jsonObject.isEmpty() ) return false;

  QSqlQuery query(implementation->database);
  QString sqlStatement = "INSERT OR REPLACE INTO " + tableName
    +  " (id, name, phone, cellphone, mail , street, city, post_code) "
    +  "  VALUES "
    +  " (:id, :name, :phone, :cellphone, :mail, :street, :city, :post_code)";

  query.prepare(sqlStatement);
  if ( query.lastError().type() != QSqlError::NoError ) {
    std::cout << "Can't Prepare sql file: "
              << query.lastError().text().toStdString() << std::endl;
    return false;
  }

  query.bindValue(":id",          QVariant(id) );
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

bool DatabaseController::deleteRow(const QString &tableName
                                 , const QString &id) const
{
  if ( tableName.isEmpty() ) return false;
  if ( id.isEmpty() ) return false;

  QSqlQuery query(implementation->database);
  QString sqlStatement = "DELETE FROM " + tableName   + " WHERE id = :id";

  if ( ! query.prepare(sqlStatement) ) return false;

  query.bindValue(":id", id);

  if ( ! query.exec() ) return false;

  return query.numRowsAffected() > 0;
}

QJsonArray DatabaseController::find(const QString &tableName
                                   ,const QString &searchText) const
{
  if ( tableName.isEmpty() ) return {};
  if ( searchText.isEmpty() ) return {};

  QSqlQuery query(implementation->database);
  QString sqlStatement = "SELECT json FROM " + tableName
                       + " WHERE LOWER(json) LIKE :searchText" ;

  if ( ! query.prepare(sqlStatement) ) return {};

  query.bindValue(":searchText", QVariant("%" + searchText.toLower() + "%") );

  if ( ! query.exec() ) return {};

  QJsonArray returnValue;

  while ( query.next() ) {
    auto json = query.value(0).toByteArray();
    auto jsonDocument = QJsonDocument::fromJson(json);
    if ( jsonDocument.isObject() ) {
      returnValue.append( jsonDocument.object() );
    }
  }

  return returnValue;
}

QJsonObject DatabaseController::readRow(const QString &tableName
                                       ,const QString &id) const
{
  if ( tableName.isEmpty() ) return {};
  if ( id.isEmpty() ) return {};

  QSqlQuery query(implementation->database);
  QString sqlStatement = "SELECT json FROM " + tableName   + " WHERE id = :id";

  if ( ! query.prepare(sqlStatement) ) return {};

  query.bindValue(":id", id);

  if ( ! query.exec() ) return {};
  if ( ! query.first() ) return {};

  auto json = query.value(0).toByteArray();
  auto jsonDocument = QJsonDocument::fromJson(json);

  if ( ! jsonDocument.isObject() ) return {};

  return jsonDocument.object();
}

bool DatabaseController::updateRow(const QString &tableName
                                  ,const QString &id
                                  ,const QJsonObject &jsonObject) const
{
  if ( tableName.isEmpty() ) return false;
  if ( id.isEmpty() ) return false;
  if ( jsonObject.isEmpty() ) return false;

  QSqlQuery query(implementation->database);
  QString sqlStatement = "UPDATE " + tableName
                       + " SET json = :json  WHERE id = :id";

  if ( ! query.prepare(sqlStatement) ) return false;

  query.bindValue(":id", id);
  query.bindValue(
    ":json",
    QVariant( QJsonDocument(jsonObject).toJson(QJsonDocument::Compact) )
  );

  if ( ! query.exec() ) return false;

  return query.numRowsAffected() > 0;
 }

} //  controllers
} // lg

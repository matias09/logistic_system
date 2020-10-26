#include "databasecontroller.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>

#include <QDir>
#include <QFile>

#include <QDebug>

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

DatabaseController::DatabaseController()
{
  implementation.reset( new Implementation(this) );
}

DatabaseController::~DatabaseController() {}

bool DatabaseController::create(
    const QString &sqlStatement
   ,const std::map<QString, QVariant> &binds) const
{
  QSqlQuery query(implementation->database);

  query.prepare(sqlStatement);
  if ( query.lastError().type() != QSqlError::NoError ) {
    std::cout << "Can't Prepare sql file: "
              << query.lastError().text().toStdString() << std::endl;
    return false;
  }

  std::for_each(binds.begin(), binds.end(),
  [&](std::pair<QString, QVariant> p) {
     query.bindValue(p.first, p.second);
  });

  query.exec();
  if ( query.lastError().type() != QSqlError::NoError ) {
    std::cout << "Can't Execute sql file: "
              << query.lastError().text().toStdString() << std::endl;
    return false;
  }

  return query.numRowsAffected() > 0;
}

bool DatabaseController::remove(
    const QString &sqlStatement
   ,const std::map<QString, QVariant> &binds) const
{
  QSqlQuery query(implementation->database);

  query.prepare(sqlStatement);
  if ( query.lastError().type() != QSqlError::NoError ) {
    std::cout << "Can't Prepare sql file: "
              << query.lastError().text().toStdString() << std::endl;

    return false;
  }

  std::for_each(binds.begin(), binds.end(),
  [&](std::pair<QString, QVariant> p) {
     query.bindValue(p.first, p.second);
  });

  query.exec();
  if ( query.lastError().type() != QSqlError::NoError ) {
    std::cout << "Can't Prepare sql file: "
              << query.lastError().text().toStdString() << std::endl;

    return false;
  }

  return query.numRowsAffected() > 0;
}

QSqlQuery DatabaseController::search(
    const QString &sqlStatement
   ,const std::map<QString, QVariant> &binds) const
{
  QSqlQuery query(implementation->database);

  query.prepare(sqlStatement);
  if ( query.lastError().type() != QSqlError::NoError ) {
    std::cout << "Can't Prepare sql file: "
              << query.lastError().text().toStdString() << std::endl;

    return QSqlQuery();
  }

  std::for_each(binds.begin(), binds.end(),
  [&](std::pair<QString, QVariant> p) {
     query.bindValue(p.first, p.second);
  });

  query.exec();
  if ( query.lastError().type() != QSqlError::NoError ) {
    std::cout << "Can't Prepare sql file: "
              << query.lastError().text().toStdString() << std::endl;

    return QSqlQuery();
  }

  return query;
}

bool DatabaseController::update(
    const QString &sqlStatement
   ,const std::map<QString, QVariant> &binds) const
{
  QSqlQuery query(implementation->database);

  query.prepare(sqlStatement);
  if ( query.lastError().type() != QSqlError::NoError ) {
    std::cout << "Can't Prepare sql file: "
              << query.lastError().text().toStdString() << std::endl;
    return false;
  }

  std::for_each(binds.begin(), binds.end(),
  [&](std::pair<QString, QVariant> p) {
     query.bindValue(p.first, p.second);
  });

  query.exec();
  if ( query.lastError().type() != QSqlError::NoError ) {
    std::cout << "Can't Execute sql file: "
              << query.lastError().text().toStdString() << std::endl;
    return false;
  }

  return query.numRowsAffected() > 0;
}

int DatabaseController::getTableLastId( const QString &table ) const
{
  QSqlQuery query(implementation->database);
  QString sqlStatement = "SELECT id FROM " + table + " ORDER BY DESC";

  query.prepare(sqlStatement);
  if ( query.lastError().type() != QSqlError::NoError ) {
    std::cout << "Can't Prepare sql file: "
              << query.lastError().text().toStdString() << std::endl;

    return 0;
  }

  query.exec();
  if ( query.lastError().type() != QSqlError::NoError ) {
    std::cout << "Can't Prepare sql file: "
              << query.lastError().text().toStdString() << std::endl;

    return 0;
  }

  query.next();
  return query.value(1).toInt();
}

} //  controllers
} // lg

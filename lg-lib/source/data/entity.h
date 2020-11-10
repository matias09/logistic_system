#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QScopedPointer>

#include <lg-lib_global.h>
#include <data/datadecorator.h>
#include <data/entitycollection.h>

#include <data/stringdecorator.h>

namespace lg {
namespace data {

class LGLIBSHARED_EXPORT Entity : public QObject
{
  Q_OBJECT

public:
  explicit Entity( QObject *parent = nullptr
                   ,const QString& key = "SomeEntityKey" );
   Entity(
    QObject *parent
   ,const QString& key
   ,const QJsonObject& jsonObject);

   virtual ~Entity();

public:
  const QString& key() const;
  const QString& id() const;

  void update(const QJsonObject& jsonObject);
  QJsonObject toJson() const;

signals:
  void childEntitiesChanged();
  void dataDecoratorsChanged();
  void childCollectionsChanged(const QString &collectionKey);

protected:
  Entity* addChild(Entity *entity, const QString &key);
  EntityCollectionBase* addChildCollection(EntityCollectionBase *entityCollection);

  DataDecorator* addDataItem(DataDecorator *dataDecorator);

  void setPrimaryKey(StringDecorator *primaryKey);

protected:
  class Implementation;
  QScopedPointer<Implementation> implementation;

};

} // data
} // lg

#endif // ENTITY_H

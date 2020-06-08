#include "ItemTemplate.h"

#include "ItemProperty/ItemPropertyFactory.h"

#include <QtGlobal>
#include <QJsonValue>
#include <QJsonArray>

namespace ItemSystem
{
    ItemTemplate::ItemTemplate()
    {
    }

    ItemTemplate::~ItemTemplate()
    {
    }

    void ItemTemplate::read(const QJsonObject& itemJsonObject)
    {
        readTag(itemJsonObject);
        readName(itemJsonObject);
        readProperties(itemJsonObject);
    }

    void ItemTemplate::readTag(const QJsonObject& itemJsonObject)
    {
        QJsonValue tagJsonValue = itemJsonObject.value("tag");
        Q_ASSERT(tagJsonValue.isString());
        m_tag = tagJsonValue.toString();
    }

    void ItemTemplate::readName(const QJsonObject& itemJsonObject)
    {
        QJsonValue nameJsonValue = itemJsonObject.value("name");
        Q_ASSERT(nameJsonValue.isString());
        m_name = nameJsonValue.toString();
    }

    void ItemTemplate::readProperties(const QJsonObject& itemJsonObject)
    {
        QJsonValue propertiesJsonValue = itemJsonObject.value("properties");
        if(!propertiesJsonValue.isUndefined())
        {
            Q_ASSERT(propertiesJsonValue.isArray());
            QJsonArray propertiesJsonArray = propertiesJsonValue.toArray();
            for (QJsonValue propertyWrapperJsonValue : propertiesJsonArray)
            {
                Q_ASSERT(propertyWrapperJsonValue.isObject());
                QJsonObject propertyWrapperJsonObject = propertyWrapperJsonValue.toObject();

                QString propertyTypeTag = propertyWrapperJsonObject.keys().first();
                QJsonValue propertyJsonValue = propertyWrapperJsonObject.value(propertyTypeTag);
                Q_ASSERT(propertyJsonValue.isObject());
                QJsonObject propertyJsonObject = propertyJsonValue.toObject();

                std::shared_ptr<ItemPropertyTemplate> propertyTemplate = ItemPropertyFactory::createItemPropertyTemplate(propertyTypeTag, propertyJsonObject);
                m_propertyTemplates.append(propertyTemplate);
            }
        }
    }

    QString ItemTemplate::getTag() const
    {
        return m_tag;
    }

    QString ItemTemplate::getName() const
    {
        return m_name;
    }

    const QList<std::shared_ptr<ItemPropertyTemplate>>& ItemTemplate::getPropertyTemplates() const
    {
        return m_propertyTemplates;
    }
}

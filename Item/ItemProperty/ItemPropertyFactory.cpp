#include "ItemPropertyFactory.h"

#include <QtGlobal>

namespace ItemSystem
{
    QMap<QString, std::shared_ptr<ItemProperty>(*)(std::shared_ptr<Item>, std::shared_ptr<ItemPropertyTemplate>)> ItemPropertyFactory::m_propertyConstructors;
    QMap<QString, std::shared_ptr<ItemPropertyTemplate>(*)(const QString&)> ItemPropertyFactory::m_propertyTemplateConstructors;

    std::shared_ptr<ItemProperty> ItemPropertyFactory::createItemProperty(std::shared_ptr<Item> item, std::shared_ptr<ItemPropertyTemplate> propertyTemplate)
    {
        Q_CHECK_PTR(propertyTemplate);
        QString propertyTypeTag = propertyTemplate->getTypeTag();

        Q_ASSERT(isItemPropertyTypeRegistered(propertyTypeTag));
        auto constructProperty = m_propertyConstructors[propertyTypeTag];
        return constructProperty(item, propertyTemplate);
    }

    std::shared_ptr<ItemPropertyTemplate> ItemPropertyFactory::createItemPropertyTemplate(const QString& propertyTypeTag, const QJsonObject& jsonObject)
    {
        Q_ASSERT(isItemPropertyTemplateTypeRegistered(propertyTypeTag));
        auto constructPropertyTemplate = m_propertyTemplateConstructors[propertyTypeTag];
        std::shared_ptr<ItemPropertyTemplate> propertyTemplate = constructPropertyTemplate(propertyTypeTag);
        propertyTemplate->read(jsonObject);
        return propertyTemplate;
    }

    bool ItemPropertyFactory::isItemPropertyTypeRegistered(const QString& propertyTypeTag)
    {
        return m_propertyConstructors.contains(propertyTypeTag);
    }

    bool ItemPropertyFactory::isItemPropertyTemplateTypeRegistered(const QString& propertyTypeTag)
    {
        return m_propertyTemplateConstructors.contains(propertyTypeTag);
    }
}

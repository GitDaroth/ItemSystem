#pragma once

#include "ItemProperty.h"

#include <QMap>

namespace ItemSystem
{
    /**
    *  @ingroup item_prop_group
    *  @brief Responsible for creating/instantiating ItemProperties and ItemPropertyTemplates
    */
    class ItemPropertyFactory
    {
    public:
        static std::shared_ptr<ItemProperty> createItemProperty(std::shared_ptr<Item> item, std::shared_ptr<ItemPropertyTemplate> propertyTemplate);
        static std::shared_ptr<ItemPropertyTemplate> createItemPropertyTemplate(const QString& propertyTypeTag, const QJsonObject& jsonObject);

        /**
        *  @brief Registers a concrete ItemProperty and concrete ItemPropertyTemplate class with a type tag referencing the ItemProperty in the JSON-File
        */
        template<typename PropertyType, typename PropertyTemplateType>
        static void registerType(const QString& propertyTypeTag)
        {
            static_assert(std::is_base_of<ItemProperty, PropertyType>::value, "PropertyType must inherit from ItemProperty!");
            static_assert(std::is_base_of<ItemPropertyTemplate, PropertyTemplateType>::value, "PropertyTemplateType must inherit from ItemPropertyTemplate!");
            m_propertyConstructors[propertyTypeTag] = &instantiateItemProperty<PropertyType>;
            m_propertyTemplateConstructors[propertyTypeTag] = &instantiateItemPropertyTemplate<PropertyTemplateType>;
        }

    private:
        static bool isItemPropertyTypeRegistered(const QString& propertyTypeTag);
        static bool isItemPropertyTemplateTypeRegistered(const QString& propertyTypeTag);

        template<typename PropertyType>
        static std::shared_ptr<ItemProperty> instantiateItemProperty(std::shared_ptr<Item> item, std::shared_ptr<ItemPropertyTemplate> propertyTemplate)
        {
            static_assert(std::is_base_of<ItemProperty, PropertyType>::value, "PropertyType must inherit from ItemProperty!");
            return std::make_shared<PropertyType>(item, propertyTemplate);
        }

        template<typename PropertyTemplateType>
        static std::shared_ptr<ItemPropertyTemplate> instantiateItemPropertyTemplate(const QString& typeTag)
        {
            static_assert(std::is_base_of<ItemPropertyTemplate, PropertyTemplateType>::value, "PropertyTemplateType must inherit from ItemPropertyTemplate!");
            return std::make_shared<PropertyTemplateType>(typeTag);
        }

        static QMap<QString, std::shared_ptr<ItemProperty>(*)(std::shared_ptr<Item>, std::shared_ptr<ItemPropertyTemplate>)> m_propertyConstructors;
        static QMap<QString, std::shared_ptr<ItemPropertyTemplate>(*)(const QString&)> m_propertyTemplateConstructors;
    };
}

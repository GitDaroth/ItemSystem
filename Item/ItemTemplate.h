#pragma once

#include "ItemProperty/ItemPropertyTemplate.h"

#include <memory>
#include <QList>

namespace ItemSystem
{
    class ItemTemplate : public Template
    {
    public:
        ItemTemplate();
        ~ItemTemplate();

        virtual void read(const QJsonObject& itemJsonObject) override;

        QString getTag() const;
        QString getName() const;
        const QList<std::shared_ptr<ItemPropertyTemplate>>& getPropertyTemplates() const;

        template<typename PropertyTemplateType>
        bool hasPropertyTemplate() const
        {
            static_assert(std::is_base_of<ItemPropertyTemplate, PropertyTemplateType>::value, "PropertyTemplateType must inherit from ItemPropertyTemplate!");
            for (std::shared_ptr<ItemPropertyTemplate> propertyTemplate : m_propertyTemplates)
            {
                if (std::dynamic_pointer_cast<PropertyTemplateType>(propertyTemplate))
                    return true;
            }
            return false;
        }

        template<typename PropertyTemplateType>
        std::shared_ptr<PropertyTemplateType> getPropertyTemplate()
        {
            static_assert(std::is_base_of<ItemPropertyTemplate, PropertyTemplateType>::value, "PropertyTemplateType must inherit from ItemPropertyTemplate!");
            for (std::shared_ptr<ItemPropertyTemplate> propertyTemplate : m_propertyTemplates)
            {
                if (std::dynamic_pointer_cast<PropertyTemplateType>(propertyTemplate))
                    return std::dynamic_pointer_cast<PropertyTemplateType>(propertyTemplate);
            }
            return nullptr;
        }

    protected:
        QString m_tag;
        QString m_name;
        QList<std::shared_ptr<ItemPropertyTemplate>> m_propertyTemplates;

    private:
        void readTag(const QJsonObject& itemJsonObject);
        void readName(const QJsonObject& itemJsonObject);
        void readProperties(const QJsonObject& itemJsonObject);
    };
}

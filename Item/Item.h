#pragma once

#include "ItemTemplate.h"
#include "../Effect/EffectTarget.h"

namespace ItemSystem
{
    class ItemProperty;

    class Item : public EffectTarget, public std::enable_shared_from_this<Item>
    {
    public:
        Item(const unsigned int instanceId, std::shared_ptr<ItemTemplate> itemTemplate);
        ~Item();

        void initialize();
        void initialize(std::shared_ptr<Item> itemToBeCopied);
        virtual void update(float deltaTime) override;

        QString getTag() const;
        QString getName() const;
        unsigned int getId() const;
        const QList<std::shared_ptr<ItemProperty>>& getProperties() const;
        std::shared_ptr<ItemTemplate> getTemplate();

        template<typename PropertyType>
        bool hasProperty() const
        {
            static_assert(std::is_base_of<ItemProperty, PropertyType>::value, "PropertyType must inherit from ItemProperty!");
            for (std::shared_ptr<ItemProperty> property : m_properties)
            {
                if (std::dynamic_pointer_cast<PropertyType>(property))
                    return true;
            }
            return false;
        }

        template<typename PropertyType>
        std::shared_ptr<PropertyType> getProperty()
        {
            static_assert(std::is_base_of<ItemProperty, PropertyType>::value, "PropertyType must inherit from ItemProperty!");
            for (std::shared_ptr<ItemProperty> property : m_properties)
            {
                if (std::dynamic_pointer_cast<PropertyType>(property))
                    return std::dynamic_pointer_cast<PropertyType>(property);
            }
            return nullptr;
        }

    protected:
        const unsigned int m_instanceId;
        std::shared_ptr<ItemTemplate> m_template;
        QList<std::shared_ptr<ItemProperty>> m_properties;
    };
}

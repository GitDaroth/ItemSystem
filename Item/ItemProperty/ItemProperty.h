#pragma once

#include "ItemPropertyTemplate.h"
#include "../Item.h"

#include <memory>

namespace ItemSystem
{
    class ItemProperty
    {
    public:
        ItemProperty(std::shared_ptr<Item> item, std::shared_ptr<ItemPropertyTemplate> propertyTemplate);
        virtual ~ItemProperty();

        virtual std::shared_ptr<ItemProperty> copy() const = 0;
        virtual void update(float deltaTime) = 0;

        QString getTypeTag() const;

    protected:
        std::shared_ptr<Item> m_item;
        std::shared_ptr<ItemPropertyTemplate> m_propertyTemplate;
    };
}

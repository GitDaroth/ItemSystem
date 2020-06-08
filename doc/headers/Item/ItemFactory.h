#pragma once

#include "Item.h"

namespace ItemSystem
{
    /**
    *  @ingroup item_group
    *  @brief Responsible for creating/instantiating Items and ItemTemplates
    */
    class ItemFactory
    {
    public:
        static std::shared_ptr<Item> createItem(const QString& itemTag);
        static std::shared_ptr<ItemTemplate> createItemTemplate(const QJsonObject& itemJsonObject);
        static std::shared_ptr<Item> copyItem(std::shared_ptr<Item> itemToBeCopied);

    private:
        static unsigned int m_itemInstanceCounter;
    };
}

#pragma once

#include "ItemLoot.h"

#include <QJsonArray>

namespace ItemSystem
{
    /**
    *  @ingroup item_loot
    *  @brief Consists of multiple ItemLoots
    */
    class ItemLootSet
    {
    public:
        ItemLootSet(const QJsonArray& lootSetJsonArray);
        ~ItemLootSet();

        /**
        *  @brief Randomly take a listed ItemLoot by its chance and create its loot
        */
        QList<std::shared_ptr<Item>> createLoot();

    private:
        void read(const QJsonArray& lootSetJsonArray);

        QList<std::shared_ptr<ItemLoot>> m_itemLoots;
        QRandomGenerator m_randomGenerator;
    };
}

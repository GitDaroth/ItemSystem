#pragma once

#include "ItemLoot.h"

#include <QJsonArray>

namespace ItemSystem
{
    class ItemLootSet
    {
    public:
        ItemLootSet(const QJsonArray& lootSetJsonArray);
        ~ItemLootSet();

        QList<std::shared_ptr<Item>> createLoot();

    private:
        void read(const QJsonArray& lootSetJsonArray);

        QList<std::shared_ptr<ItemLoot>> m_itemLoots;
        QRandomGenerator m_randomGenerator;
    };
}

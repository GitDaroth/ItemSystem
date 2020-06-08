#pragma once

#include "ItemLootSet.h"

namespace ItemSystem
{
    /**
    *  @ingroup item_loot
    *  @brief Consists of multiple ItemLootSets
    */
    class ItemLootList
    {
    public:
        ItemLootList(const QJsonObject& jsonObject);
        ~ItemLootList();

        /**
        *  @brief Create loot of listed ItemLootSets
        */
        QList<std::shared_ptr<Item>> createLoot();

        QString getTag() const;

    private:
        void read(const QJsonObject& jsonObject);
        void readTag(const QJsonObject& jsonObject);
        void readItemLootSets(const QJsonObject& jsonObject);

        QString m_tag;
        QList<std::shared_ptr<ItemLootSet>> m_itemLootSets;
    };
}

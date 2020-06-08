#pragma once

#include "ItemLootList.h"

namespace ItemSystem
{
    /**
    *  @ingroup item_loot
    *  @brief Holds all ItemLootLists that have been read in
    */
    class ItemLootListManager
    {
    public:
        ~ItemLootListManager();
        static std::shared_ptr<ItemLootListManager> getInstance();

        /**
        *  @brief Reads in all ItemLootLists from a JSON file located at the given path
        */
        void readItemLootLists(const QString& filePath);
        std::shared_ptr<ItemLootList> getItemLootListByTag(const QString& tag);
        bool hasItemLootListWithTag(const QString& tag);

        const QList<std::shared_ptr<ItemLootList>>& getItemLootLists();

    private:
        ItemLootListManager();

        static std::shared_ptr<ItemLootListManager> m_instance;
        QList<std::shared_ptr<ItemLootList>> m_itemLootLists;
    };
}

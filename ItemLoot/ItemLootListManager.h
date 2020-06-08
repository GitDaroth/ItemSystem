#pragma once

#include "ItemLootList.h"

namespace ItemSystem
{
    class ItemLootListManager
    {
    public:
        ~ItemLootListManager();
        static std::shared_ptr<ItemLootListManager> getInstance();

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

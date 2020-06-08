#include "ItemLootList.h"

namespace ItemSystem
{
    ItemLootList::ItemLootList(const QJsonObject& jsonObject)
    {
        read(jsonObject);
    }

    ItemLootList::~ItemLootList()
    {
    }

    QList<std::shared_ptr<Item>> ItemLootList::createLoot()
    {
        QList<std::shared_ptr<Item>> totalLoot;
        for(std::shared_ptr<ItemLootSet> lootSet : m_itemLootSets)
        {
            for(std::shared_ptr<Item> item : lootSet->createLoot())
            {
                totalLoot.append(item);
            }
        }
        return totalLoot;
    }

    void ItemLootList::read(const QJsonObject& jsonObject)
    {
        readTag(jsonObject);
        readItemLootSets(jsonObject);
    }

    void ItemLootList::readTag(const QJsonObject& jsonObject)
    {
        QJsonValue tagJsonValue = jsonObject.value("tag");
        Q_ASSERT(tagJsonValue.isString());
        m_tag = tagJsonValue.toString();
    }

    void ItemLootList::readItemLootSets(const QJsonObject& jsonObject)
    {
        QJsonValue lootSetsJsonValue = jsonObject.value("item_loot_sets");
        Q_ASSERT(lootSetsJsonValue.isArray());
        QJsonArray lootSetsJsonArray = lootSetsJsonValue.toArray();

        for(QJsonValue lootSetWrapperJsonValue : lootSetsJsonArray)
        {
            Q_ASSERT(lootSetWrapperJsonValue.isObject());
            QJsonObject lootSetWrapperJsonObject = lootSetWrapperJsonValue.toObject();

            QJsonValue lootSetJsonValue = lootSetWrapperJsonObject.value("item_loot_set");
            Q_ASSERT(lootSetJsonValue.isArray());
            QJsonArray lootSetJsonArray = lootSetJsonValue.toArray();

            std::shared_ptr<ItemLootSet> lootSet = std::make_shared<ItemLootSet>(lootSetJsonArray);
            m_itemLootSets.append(lootSet);
        }
    }

    QString ItemLootList::getTag() const
    {
        return m_tag;
    }
}

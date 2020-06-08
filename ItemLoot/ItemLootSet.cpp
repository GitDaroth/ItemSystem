#include "ItemLootSet.h"

namespace ItemSystem
{
    ItemLootSet::ItemLootSet(const QJsonArray& lootSetJsonArray)
    {
        read(lootSetJsonArray);
        m_randomGenerator = QRandomGenerator::securelySeeded();
    }

    ItemLootSet::~ItemLootSet()
    {
    }

    QList<std::shared_ptr<Item>> ItemLootSet::createLoot()
    {
        float randomValue = m_randomGenerator.generateDouble();
        float accumulatedChance = 0.f;
        for(std::shared_ptr<ItemLoot> itemLoot : m_itemLoots)
        {
            accumulatedChance += itemLoot->getChance();
            if(randomValue <= accumulatedChance)
            {
                return itemLoot->createLoot();
            }
        }
        QList<std::shared_ptr<Item>> emptyLoot;
        return emptyLoot;
    }

    void ItemLootSet::read(const QJsonArray& lootSetJsonArray)
    {
        for (QJsonValue lootWrapperJsonValue : lootSetJsonArray)
        {
            Q_ASSERT(lootWrapperJsonValue.isObject());
            QJsonObject lootWrapperJsonObject = lootWrapperJsonValue.toObject();

            QJsonValue lootJsonValue = lootWrapperJsonObject.value("item_loot");
            Q_ASSERT(lootJsonValue.isObject());
            QJsonObject lootJsonObject = lootJsonValue.toObject();

            m_itemLoots.append(std::make_shared<ItemLoot>(lootJsonObject));
        }
    }
}

#include "ItemLoot.h"

#include "../ItemCondition/ItemConditionFactory.h"
#include "../Item/ItemTemplateManager.h"
#include "../Item/ItemFactory.h"
#include "../Item/ItemProperty/StackableProp.h"

namespace ItemSystem
{
    ItemLoot::ItemLoot(const QJsonObject& jsonObject)
    {
        read(jsonObject);
        m_randomGenerator = QRandomGenerator::securelySeeded();
    }

    ItemLoot::~ItemLoot()
    {
    }

    QList<std::shared_ptr<Item>> ItemLoot::createLoot()
    {
        QList<std::shared_ptr<Item>> loot;
        QList<std::shared_ptr<ItemTemplate>> itemTemplates = ItemTemplateManager::getInstance()->getItemTemplates();
        QList<std::shared_ptr<ItemTemplate>> itemTemplatesByCondition;

        for(auto itemTemplate : itemTemplates)
        {
            if(m_itemCondition->evaluate(itemTemplate))
                itemTemplatesByCondition.append(itemTemplate);
        }

        if(itemTemplatesByCondition.size() == 0)
            return loot;

        unsigned int randomItemTemplateIndex = m_randomGenerator.generateDouble() * itemTemplatesByCondition.size();
        std::shared_ptr<ItemTemplate> randomItemTemplate = itemTemplatesByCondition[randomItemTemplateIndex];

        if(randomItemTemplate->hasPropertyTemplate<StackablePropTemplate>())
        {
            unsigned int maxStacks = randomItemTemplate->getPropertyTemplate<StackablePropTemplate>()->getMaxStacks();

            for(unsigned int i = 0; i < m_amount / maxStacks; i++)
            {
                std::shared_ptr<Item> craftedItem = ItemFactory::createItem(randomItemTemplate->getTag());
                craftedItem->getProperty<StackableProp>()->setCurrentStacks(maxStacks);
                loot.append(craftedItem);
            }

            if((m_amount % maxStacks) > 0)
            {
                std::shared_ptr<Item> craftedItem = ItemFactory::createItem(randomItemTemplate->getTag());
                craftedItem->getProperty<StackableProp>()->setCurrentStacks(m_amount % maxStacks);
                loot.append(craftedItem);
            }
        }
        else
        {
            for(unsigned int i = 0; i < m_amount; i++)
                loot.append(ItemFactory::createItem(randomItemTemplate->getTag()));
        }

        return loot;
    }

    void ItemLoot::read(const QJsonObject& jsonObject)
    {
        readAmount(jsonObject);
        readChance(jsonObject);
        readItemCondition(jsonObject);
    }

    void ItemLoot::readAmount(const QJsonObject& jsonObject)
    {
        QJsonValue amountJsonValue = jsonObject.value("amount");
        Q_ASSERT(amountJsonValue.isDouble());
        Q_ASSERT((int)amountJsonValue.toDouble() > 0);
        m_amount = (unsigned int)amountJsonValue.toDouble();
    }

    void ItemLoot::readChance(const QJsonObject& jsonObject)
    {
        QJsonValue chanceJsonValue = jsonObject.value("chance");
        Q_ASSERT(chanceJsonValue.isDouble());
        m_chance = (float)chanceJsonValue.toDouble();
    }

    void ItemLoot::readItemCondition(const QJsonObject& jsonObject)
    {
        Q_ASSERT(jsonObject.keys().size() == 3);
        QString itemConditionType;
        for(QString key : jsonObject.keys())
        {
            if(key != "amount" && key != "chance")
                itemConditionType = key;
        }

        QJsonValue itemConditionJsonValue = jsonObject.value(itemConditionType);
        Q_ASSERT(itemConditionJsonValue.isObject());
        QJsonObject itemConditionJsonObject = itemConditionJsonValue.toObject();

        m_itemCondition = ItemConditionFactory::createItemCondition(itemConditionType, itemConditionJsonObject);
    }

    unsigned int ItemLoot::getAmount() const
    {
        return m_amount;
    }

    float ItemLoot::getChance() const
    {
        return m_chance;
    }
}

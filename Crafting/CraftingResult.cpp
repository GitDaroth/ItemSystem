#include "CraftingResult.h"

#include "../ItemCondition/ItemConditionFactory.h"
#include "../Item/ItemTemplateManager.h"
#include "../Item/ItemFactory.h"
#include "../Item/ItemProperty/StackableProp.h"

#include <QtGlobal>

namespace ItemSystem
{
    CraftingResult::CraftingResult(const QJsonObject& jsonObject)
    {
        read(jsonObject);
        m_randomGenerator = QRandomGenerator::securelySeeded();
    }

    CraftingResult::~CraftingResult()
    {
    }

    QList<std::shared_ptr<Item>> CraftingResult::createResult()
    {
        QList<std::shared_ptr<Item>> craftedItems;
        QList<std::shared_ptr<ItemTemplate>> itemTemplates = ItemTemplateManager::getInstance()->getItemTemplates();
        QList<std::shared_ptr<ItemTemplate>> itemTemplatesByCondition;

        for(auto itemTemplate : itemTemplates)
        {
            if(m_itemCondition->evaluate(itemTemplate))
                itemTemplatesByCondition.append(itemTemplate);
        }

        if(itemTemplatesByCondition.size() == 0)
            return craftedItems;

        unsigned int randomItemTemplateIndex = m_randomGenerator.generateDouble() * itemTemplatesByCondition.size();
        std::shared_ptr<ItemTemplate> randomItemTemplate = itemTemplatesByCondition[randomItemTemplateIndex];

        if(randomItemTemplate->hasPropertyTemplate<StackablePropTemplate>())
        {
            unsigned int maxStacks = randomItemTemplate->getPropertyTemplate<StackablePropTemplate>()->getMaxStacks();

            for(unsigned int i = 0; i < m_amount / maxStacks; i++)
            {
                std::shared_ptr<Item> craftedItem = ItemFactory::createItem(randomItemTemplate->getTag());
                craftedItem->getProperty<StackableProp>()->setCurrentStacks(maxStacks);
                craftedItems.append(craftedItem);
            }

            if((m_amount % maxStacks) > 0)
            {
                std::shared_ptr<Item> craftedItem = ItemFactory::createItem(randomItemTemplate->getTag());
                craftedItem->getProperty<StackableProp>()->setCurrentStacks(m_amount % maxStacks);
                craftedItems.append(craftedItem);
            }
        }
        else
        {
            for(unsigned int i = 0; i < m_amount; i++)
                craftedItems.append(ItemFactory::createItem(randomItemTemplate->getTag()));
        }

        return craftedItems;
    }

    void CraftingResult::read(const QJsonObject& jsonObject)
    {
        readAmount(jsonObject);
        readItemCondition(jsonObject);
    }

    void CraftingResult::readAmount(const QJsonObject& jsonObject)
    {
        QJsonValue amountJsonValue = jsonObject.value("amount");
        Q_ASSERT(amountJsonValue.isDouble());
        Q_ASSERT((int)amountJsonValue.toDouble() > 0);
        m_amount = (unsigned int)amountJsonValue.toDouble();
    }

    void CraftingResult::readItemCondition(const QJsonObject& jsonObject)
    {
        Q_ASSERT(jsonObject.keys().size() == 2);

        QString itemConditionType;
        for(QString key : jsonObject.keys())
        {
            if(key != "amount")
                itemConditionType = key;
        }

        QJsonValue itemConditionJsonValue = jsonObject.value(itemConditionType);
        Q_ASSERT(itemConditionJsonValue.isObject());
        QJsonObject itemConditionJsonObject = itemConditionJsonValue.toObject();

        m_itemCondition = ItemConditionFactory::createItemCondition(itemConditionType, itemConditionJsonObject);
    }

    unsigned int CraftingResult::getAmount() const
    {
        return m_amount;
    }
}


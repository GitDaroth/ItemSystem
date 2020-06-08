#include "CraftingRecipe.h"

#include "../Item/ItemProperty/StackableProp.h"

#include <QJsonArray>

namespace ItemSystem
{
    CraftingRecipe::CraftingRecipe(const QJsonObject& jsonObject)
    {
        read(jsonObject);
    }

    CraftingRecipe::~CraftingRecipe()
    {
    }

    bool CraftingRecipe::craft(std::shared_ptr<ItemContainer> itemContainer, unsigned int amount)
    {
        QList<std::shared_ptr<Item>> requiredItems;

        for(std::shared_ptr<CraftingRequirement> requirement : m_requirements)
        {
            unsigned int requiredAmount = requirement->getAmount() * amount;

            QList<std::shared_ptr<Item>> items = itemContainer->getItems();
            for(std::shared_ptr<Item> item : items)
            {
                if(requirement->check(item))
                {
                    if(item->hasProperty<StackableProp>())
                    {
                        std::shared_ptr<StackableProp> stackableProp = item->getProperty<StackableProp>();
                        unsigned int currentStacks = stackableProp->getCurrentStacks();
                        if(currentStacks <= requiredAmount)
                        {
                            requiredAmount -= currentStacks;
                            requiredItems.append(item);
                            itemContainer->removeItemById(item->getId());
                        }
                        else
                        {
                            requiredItems.append(stackableProp->splitItem(requiredAmount));
                            requiredAmount = 0;
                        }
                    }
                    else
                    {
                        requiredAmount--;
                        requiredItems.append(item);
                        itemContainer->removeItemById(item->getId());
                    }
                }

                if(requiredAmount == 0)
                    break;
            }

            if(requiredAmount > 0)
            {
                for(std::shared_ptr<Item> item : requiredItems)
                    itemContainer->addItem(item);
                return false;
            }
        }

        for(std::shared_ptr<CraftingResult> result : m_results)
        {
            for(std::shared_ptr<Item> craftedItem : result->createResult())
            {
                itemContainer->addItem(craftedItem);
            }
        }

        return true;
    }

    void CraftingRecipe::read(const QJsonObject& jsonObject)
    {
        readTag(jsonObject);
        readRequirements(jsonObject);
        readResults(jsonObject);
    }

    void CraftingRecipe::readTag(const QJsonObject& jsonObject)
    {
        QJsonValue tagJsonValue = jsonObject.value("tag");
        Q_ASSERT(tagJsonValue.isString());
        m_tag = tagJsonValue.toString();
    }

    void CraftingRecipe::readRequirements(const QJsonObject& jsonObject)
    {
        QJsonValue requirementsJsonValue = jsonObject.value("crafting_requirements");
        Q_ASSERT(requirementsJsonValue.isArray());
        QJsonArray requirementsJsonArray = requirementsJsonValue.toArray();

        for(QJsonValue requirementWrapperJsonValue : requirementsJsonArray)
        {
            Q_ASSERT(requirementWrapperJsonValue.isObject());
            QJsonObject requirementWrapperJsonObject = requirementWrapperJsonValue.toObject();

            QJsonValue requirementJsonValue = requirementWrapperJsonObject.value("crafting_requirement");
            Q_ASSERT(requirementJsonValue.isObject());
            QJsonObject requirementJsonObject = requirementJsonValue.toObject();

            std::shared_ptr<CraftingRequirement> requirement = std::make_shared<CraftingRequirement>(requirementJsonObject);
            m_requirements.append(requirement);
        }
    }

    void CraftingRecipe::readResults(const QJsonObject& jsonObject)
    {
        QJsonValue resultsJsonValue = jsonObject.value("crafting_results");
        Q_ASSERT(resultsJsonValue.isArray());
        QJsonArray resultsJsonArray = resultsJsonValue.toArray();

        for(QJsonValue resultWrapperJsonValue : resultsJsonArray)
        {
            Q_ASSERT(resultWrapperJsonValue.isObject());
            QJsonObject resultWrapperJsonObject = resultWrapperJsonValue.toObject();

            QJsonValue resultJsonValue = resultWrapperJsonObject.value("crafting_result");
            Q_ASSERT(resultJsonValue.isObject());
            QJsonObject resultJsonObject = resultJsonValue.toObject();

            std::shared_ptr<CraftingResult> result = std::make_shared<CraftingResult>(resultJsonObject);
            m_results.append(result);
        }
    }

    QString CraftingRecipe::getTag() const
    {
        return m_tag;
    }
}

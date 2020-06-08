#pragma once

#include "../ItemCondition/ItemCondition.h"
#include "../Item/Item.h"

#include <QRandomGenerator>

namespace ItemSystem
{
    /**
    *  @ingroup crafting
    *  @brief Responsible for creating the crafted Items
    */
    class CraftingResult
    {
    public:
        CraftingResult(const QJsonObject& jsonObject);
        ~CraftingResult();

        /**
        *  @brief Creates the result by randomly picking an ItemTemplate that matches the ItemCondition
        */
        QList<std::shared_ptr<Item>> createResult();

        unsigned int getAmount() const;

    private:
        void read(const QJsonObject& jsonObject);
        void readAmount(const QJsonObject& jsonObject);
        void readItemCondition(const QJsonObject& jsonObject);

        unsigned int m_amount;
        std::shared_ptr<ItemCondition> m_itemCondition;
        QRandomGenerator m_randomGenerator;
    };
}

#pragma once

#include "../ItemCondition/ItemCondition.h"
#include "../Item/Item.h"

namespace ItemSystem
{
    /**
    *  @ingroup crafting
    *  @brief Holds the condition and the amount for the requirement
    */
    class CraftingRequirement
    {
    public:
        CraftingRequirement(const QJsonObject& jsonObject);
        ~CraftingRequirement();

        /**
        *  @brief Checks if the given Item matches with the requirement condition
        */
        bool check(std::shared_ptr<Item> item) const;

        unsigned int getAmount() const;

    private:
        void read(const QJsonObject& jsonObject);
        void readAmount(const QJsonObject& jsonObject);
        void readItemCondition(const QJsonObject& jsonObject);

        unsigned int m_amount;
        std::shared_ptr<ItemCondition> m_itemCondition;
    };
}

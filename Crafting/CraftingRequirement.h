#pragma once

#include "../ItemCondition/ItemCondition.h"
#include "../Item/Item.h"

namespace ItemSystem
{
    class CraftingRequirement
    {
    public:
        CraftingRequirement(const QJsonObject& jsonObject);
        ~CraftingRequirement();

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

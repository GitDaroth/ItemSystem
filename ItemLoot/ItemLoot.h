#pragma once

#include "../ItemCondition/ItemCondition.h"
#include "../Item/Item.h"

#include <QRandomGenerator>

namespace ItemSystem
{
    class ItemLoot
    {
    public:
        ItemLoot(const QJsonObject& jsonObject);
        ~ItemLoot();

        QList<std::shared_ptr<Item>> createLoot();

        unsigned int getAmount() const;
        float getChance() const;

    private:
        void read(const QJsonObject& jsonObject);
        void readAmount(const QJsonObject& jsonObject);
        void readChance(const QJsonObject& jsonObject);
        void readItemCondition(const QJsonObject& jsonObject);

        unsigned int m_amount;
        float m_chance;
        std::shared_ptr<ItemCondition> m_itemCondition;
        QRandomGenerator m_randomGenerator;
    };
}

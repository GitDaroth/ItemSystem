#pragma once

#include "../Item/Item.h"
#include "../ItemCondition/ItemCondition.h"

namespace ItemSystem
{
    class EquipmentSlot
    {
    public:
        EquipmentSlot(const QJsonObject& jsonObject);
        ~EquipmentSlot();

        std::shared_ptr<Item> insertItem(std::shared_ptr<Item> item);
        std::shared_ptr<Item> takeItem();
        std::shared_ptr<Item> getItem();
        bool doesItemFit(std::shared_ptr<Item> item) const;
        bool isEmpty() const;

        QString getTag() const;

    private:
        void read(const QJsonObject& jsonObject);
        void readTag(const QJsonObject& jsonObject);
        void readItemCondition(const QJsonObject& jsonObject);

        QString m_tag;
        std::shared_ptr<Item> m_item;
        std::shared_ptr<ItemCondition> m_itemCondition;
    };
}

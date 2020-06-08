#pragma once

#include "../Item/Item.h"

namespace ItemSystem
{
    class ItemContainer
    {
    public:
        ItemContainer(unsigned int capacity);
        virtual ~ItemContainer();

        virtual void triggerItem(unsigned int index, const QString& inputType) = 0;

        bool addItem(std::shared_ptr<Item> item);
        bool removeItem(std::shared_ptr<Item> item);
        bool removeItemById(unsigned int itemId);
        void removeAllItems();

        const QList<std::shared_ptr<Item>>& getItems();
        unsigned int getItemCount() const;
        unsigned int getCapacity() const;
        void setCapacity(unsigned int capacity);

    protected:
        unsigned int m_capacity;
        QList<std::shared_ptr<Item>> m_items;
    };
}

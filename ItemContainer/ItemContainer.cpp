#include "ItemContainer.h"

namespace ItemSystem
{
    ItemContainer::ItemContainer(unsigned int capacity) :
        m_capacity(capacity)
    {
    }

    ItemContainer::~ItemContainer()
    {
    }

    bool ItemContainer::addItem(std::shared_ptr<Item> item)
    {
        if ((unsigned int)m_items.size() < m_capacity)
        {
            m_items.append(item);
            return true;
        }
        return false;
    }

    bool ItemContainer::removeItem(std::shared_ptr<Item> item)
    {
        return removeItemById(item->getId());
    }

    bool ItemContainer::removeItemById(unsigned int itemId)
    {
        for (int i = 0; i < m_items.size(); i++)
        {
            if (m_items[i]->getId() == itemId)
            {
                m_items.removeAt(i);
                return true;
            }
        }
        return false;
    }

    void ItemContainer::removeAllItems()
    {
        m_items.clear();
    }

    const QList<std::shared_ptr<Item>>& ItemContainer::getItems()
    {
        return m_items;
    }

    unsigned int ItemContainer::getItemCount() const
    {
        return m_items.size();
    }

    unsigned int ItemContainer::getCapacity() const
    {
        return m_capacity;
    }

    void ItemContainer::setCapacity(unsigned int capacity)
    {
        m_capacity = capacity;
    }
}

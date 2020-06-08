#include "ItemFactory.h"

#include <QtGlobal>
#include "ItemTemplateManager.h"

namespace ItemSystem
{
    unsigned int ItemFactory::m_itemInstanceCounter = 0;

    std::shared_ptr<Item> ItemFactory::createItem(const QString& itemTag)
    {
        std::shared_ptr<ItemTemplate> itemTemplate = ItemTemplateManager::getInstance()->getItemTemplateByTag(itemTag);
        Q_CHECK_PTR(itemTemplate);
        unsigned int instanceId = m_itemInstanceCounter;
        m_itemInstanceCounter++;
        std::shared_ptr<Item> item = std::make_shared<Item>(instanceId, itemTemplate);
        item->initialize();
        return item;
    }

    std::shared_ptr<ItemTemplate> ItemFactory::createItemTemplate(const QJsonObject& itemJsonObject)
    {
        std::shared_ptr<ItemTemplate> itemTemplate = std::make_shared<ItemTemplate>();
        itemTemplate->read(itemJsonObject);
        return itemTemplate;
    }

    std::shared_ptr<Item> ItemFactory::copyItem(std::shared_ptr<Item> itemToBeCopied)
    {
        unsigned int instanceId = m_itemInstanceCounter;
        m_itemInstanceCounter++;
        std::shared_ptr<Item> copiedItem = std::make_shared<Item>(instanceId, itemToBeCopied->getTemplate());
        copiedItem->initialize(itemToBeCopied);
        return copiedItem;
    }
}

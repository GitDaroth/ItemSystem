#include "ItemLootListManager.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QtGlobal>

namespace ItemSystem
{
    std::shared_ptr<ItemLootListManager> ItemLootListManager::m_instance = nullptr;

    ItemLootListManager::ItemLootListManager()
    {
    }

    ItemLootListManager::~ItemLootListManager()
    {
    }

    std::shared_ptr<ItemLootListManager> ItemLootListManager::getInstance()
    {
        if (m_instance == nullptr)
            m_instance = std::shared_ptr<ItemLootListManager>(new ItemLootListManager());
        return m_instance;
    }

    void ItemLootListManager::readItemLootLists(const QString& filePath)
    {
        QFile file(filePath);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString jsonString = file.readAll();
        file.close();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());

        Q_ASSERT(jsonDoc.isArray());
        QJsonArray itemLootListsJsonArray = jsonDoc.array();
        for (QJsonValue itemLootListWrapperJsonValue : itemLootListsJsonArray)
        {
            Q_ASSERT(itemLootListWrapperJsonValue.isObject());
            QJsonObject itemLootListWrapperJsonObject = itemLootListWrapperJsonValue.toObject();

            QJsonValue itemLootListJsonValue = itemLootListWrapperJsonObject.value("item_loot_list");
            Q_ASSERT(itemLootListJsonValue.isObject());
            QJsonObject itemLootListJsonObject = itemLootListJsonValue.toObject();

            m_itemLootLists.append(std::make_shared<ItemLootList>(itemLootListJsonObject));
        }
    }

    std::shared_ptr<ItemLootList> ItemLootListManager::getItemLootListByTag(const QString& tag)
    {
        for (std::shared_ptr<ItemLootList> itemLootList : m_itemLootLists)
        {
            if (itemLootList->getTag() == tag)
                return itemLootList;
        }
        return nullptr;
    }

    bool ItemLootListManager::hasItemLootListWithTag(const QString& tag)
    {
        for (std::shared_ptr<ItemLootList> itemLootList : m_itemLootLists)
        {
            if (itemLootList->getTag() == tag)
                return true;
        }
        return false;
    }

    const QList<std::shared_ptr<ItemLootList>>& ItemLootListManager::getItemLootLists()
    {
        return m_itemLootLists;
    }
}

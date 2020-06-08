#include "ItemTemplateManager.h"

#include "ItemFactory.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QtGlobal>

namespace ItemSystem
{
    std::shared_ptr<ItemTemplateManager> ItemTemplateManager::m_instance = nullptr;

    ItemTemplateManager::ItemTemplateManager()
    {
    }

    ItemTemplateManager::~ItemTemplateManager()
    {
    }

    std::shared_ptr<ItemTemplateManager> ItemTemplateManager::getInstance()
    {
        if (m_instance == nullptr)
            m_instance = std::shared_ptr<ItemTemplateManager>(new ItemTemplateManager());
        return m_instance;
    }

    void ItemTemplateManager::readItemTemplates(const QString& filePath)
    {
        QFile file(filePath);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString jsonString = file.readAll();
        file.close();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());

        Q_ASSERT(jsonDoc.isArray());
        QJsonArray itemsJsonArray = jsonDoc.array();
        for (QJsonValue itemWrapperJsonValue : itemsJsonArray)
        {
            Q_ASSERT(itemWrapperJsonValue.isObject());
            QJsonObject itemWrapperJsonObject = itemWrapperJsonValue.toObject();

            QJsonValue itemJsonValue = itemWrapperJsonObject.value("item");
            Q_ASSERT(itemJsonValue.isObject());
            QJsonObject itemJsonObject = itemJsonValue.toObject();

            std::shared_ptr<ItemTemplate> itemTemplate = ItemFactory::createItemTemplate(itemJsonObject);
            m_itemTemplates.append(itemTemplate);
        }
    }

    std::shared_ptr<ItemTemplate> ItemTemplateManager::getItemTemplateByTag(const QString& itemTag)
    {
        for (std::shared_ptr<ItemTemplate> itemTemplate : m_itemTemplates)
        {
            if (itemTemplate->getTag() == itemTag)
                return itemTemplate;
        }
        return nullptr;
    }

    bool ItemTemplateManager::hasItemTemplateWithTag(const QString& itemTag)
    {
        for (std::shared_ptr<ItemTemplate> itemTemplate : m_itemTemplates)
        {
            if (itemTemplate->getTag() == itemTag)
                return true;
        }
        return false;
    }

    const QList<std::shared_ptr<ItemTemplate>>& ItemTemplateManager::getItemTemplates()
    {
        return m_itemTemplates;
    }
}

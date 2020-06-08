#pragma once

#include "ItemTemplate.h"

namespace ItemSystem
{
    class ItemTemplateManager
    {
    public:
        ~ItemTemplateManager();
        static std::shared_ptr<ItemTemplateManager> getInstance();

        void readItemTemplates(const QString& filePath);
        std::shared_ptr<ItemTemplate> getItemTemplateByTag(const QString& itemTag);
        bool hasItemTemplateWithTag(const QString& itemTag);

        const QList<std::shared_ptr<ItemTemplate>>& getItemTemplates();

    private:
        ItemTemplateManager();

        static std::shared_ptr<ItemTemplateManager> m_instance;
        QList<std::shared_ptr<ItemTemplate>> m_itemTemplates;
    };
}

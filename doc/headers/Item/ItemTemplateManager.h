#pragma once

#include "ItemTemplate.h"

namespace ItemSystem
{
    /**
    *  @ingroup item_group
    *  @brief Holds all ItemTemplates that have been read in
    */
    class ItemTemplateManager
    {
    public:
        ~ItemTemplateManager();
        static std::shared_ptr<ItemTemplateManager> getInstance();

        /**
        *  @brief Reads in all ItemTemplates from a JSON file located at the given path
        */
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

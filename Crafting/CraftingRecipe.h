#pragma once

#include "CraftingRequirement.h"
#include "CraftingResult.h"
#include "../ItemContainer/ItemContainer.h"

namespace ItemSystem
{
    class CraftingRecipe
    {
    public:
        CraftingRecipe(const QJsonObject& jsonObject);
        ~CraftingRecipe();

        bool craft(std::shared_ptr<ItemContainer> itemContainer, unsigned int amount);

        QString getTag() const;

    private:
        void read(const QJsonObject& jsonObject);
        void readTag(const QJsonObject& jsonObject);
        void readRequirements(const QJsonObject& jsonObject);
        void readResults(const QJsonObject& jsonObject);

        QString m_tag;
        QList<std::shared_ptr<CraftingRequirement>> m_requirements;
        QList<std::shared_ptr<CraftingResult>> m_results;
    };
}

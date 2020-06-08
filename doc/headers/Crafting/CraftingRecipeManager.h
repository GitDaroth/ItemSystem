#pragma once

#include "CraftingRecipe.h"

namespace ItemSystem
{
    /**
    *  @ingroup crafting
    *  @brief Holds all CraftingRecipes that have been read in
    */
    class CraftingRecipeManager
    {
    public:
        ~CraftingRecipeManager();
        static std::shared_ptr<CraftingRecipeManager> getInstance();

        void readCraftingRecipes(const QString& filePath);
        std::shared_ptr<CraftingRecipe> getCraftingRecipeByTag(const QString& tag);
        bool hasCraftingRecipeWithTag(const QString& tag);

        const QList<std::shared_ptr<CraftingRecipe>>& getCraftingRecipes();

    private:
        CraftingRecipeManager();

        static std::shared_ptr<CraftingRecipeManager> m_instance;
        QList<std::shared_ptr<CraftingRecipe>> m_craftingRecipes;
    };
}

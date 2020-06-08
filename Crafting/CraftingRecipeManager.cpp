#include "CraftingRecipeManager.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QtGlobal>

namespace ItemSystem
{
    std::shared_ptr<CraftingRecipeManager> CraftingRecipeManager::m_instance = nullptr;

    CraftingRecipeManager::CraftingRecipeManager()
    {
    }

    CraftingRecipeManager::~CraftingRecipeManager()
    {
    }

    std::shared_ptr<CraftingRecipeManager> CraftingRecipeManager::getInstance()
    {
        if (m_instance == nullptr)
            m_instance = std::shared_ptr<CraftingRecipeManager>(new CraftingRecipeManager());
        return m_instance;
    }

    void CraftingRecipeManager::readCraftingRecipes(const QString& filePath)
    {
        QFile file(filePath);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString jsonString = file.readAll();
        file.close();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());

        Q_ASSERT(jsonDoc.isArray());
        QJsonArray recipesJsonArray = jsonDoc.array();
        for (QJsonValue recipeWrapperJsonValue : recipesJsonArray)
        {
            Q_ASSERT(recipeWrapperJsonValue.isObject());
            QJsonObject recipeWrapperJsonObject = recipeWrapperJsonValue.toObject();

            QJsonValue recipeJsonValue = recipeWrapperJsonObject.value("crafting_recipe");
            Q_ASSERT(recipeJsonValue.isObject());
            QJsonObject recipeJsonObject = recipeJsonValue.toObject();

            m_craftingRecipes.append(std::make_shared<CraftingRecipe>(recipeJsonObject));
        }
    }

    std::shared_ptr<CraftingRecipe> CraftingRecipeManager::getCraftingRecipeByTag(const QString& tag)
    {
        for (std::shared_ptr<CraftingRecipe> craftingRecipe : m_craftingRecipes)
        {
            if (craftingRecipe->getTag() == tag)
                return craftingRecipe;
        }
        return nullptr;
    }

    bool CraftingRecipeManager::hasCraftingRecipeWithTag(const QString& tag)
    {
        for (std::shared_ptr<CraftingRecipe> craftingRecipe : m_craftingRecipes)
        {
            if (craftingRecipe->getTag() == tag)
                return true;
        }
        return false;
    }

    const QList<std::shared_ptr<CraftingRecipe>>& CraftingRecipeManager::getCraftingRecipes()
    {
        return m_craftingRecipes;
    }
}

/** @defgroup crafting Crafting
 *
 *  The Crafting System is based of CraftingRecipes that may be specified in JSON files. <br>
 *  In order to craft a recipe the player need to have all CraftingRequirements. The output of a CraftingRecipe is determined by CraftingResults.<br>
 *  CraftingRequirement and CraftingResult are based on an ItemCondition to manifest which Item is needed or will be crafted.<br>
 *  <br>
 *  <b>Example JSON file for a crafting recipe</b>
 *  @code{.cpp}
 *  [
 *  	{"crafting_recipe":{
 *  		"tag": "rand_potion_recipe",
 *  		"crafting_requirements":[
 *  			{"crafting_requirement":{
 *  				"amount": 5,
 *  				"item_category_condition":{
 *  					"operator": "equal",
 *  					"value": "ingredient"
 *  				}
 *  			}}
 *  		],
 *  		"crafting_results":[
 *  			{"crafting_result":{
 *  				"amount": 1,
 *  				"item_condition_chain":{
 *  					"operator": "and",
 *  					"chained_item_conditions":[
 *  						{"item_category_condition":{
 *  							"operator": "equal",
 *  							"value": "potion"
 *  						}},
 *  						{"item_rarity_condition":{
 *  							"operator": "equal",
 *  							"value": "rare"
 *  						}}
 *  					]
 *  				}
 *  			}}
 *  		]
 *  	}}
 *  ]
 *  @endcode
 *
 *  <b>Example usage</b>
 *  @code{.cpp}
 *  CraftingRecipeManager::getInstance()->readCraftingRecipes("craftingRecipes.json");
 *  auto randPotionRecipe = CraftingRecipeManager::getInstance()->getCraftingRecipeByTag("rand_potion_recipe");
 *  unsigned int craftingAmount = 1;
 *  randPotionRecipe->craft(inventory, craftingAmount);
 *  @endcode
 *
 *  <b>Crafting module</b><br>
 *  <img src="../images/crafting_sw.png">
 */

#pragma once

#include "CraftingRequirement.h"
#include "CraftingResult.h"
#include "../ItemContainer/ItemContainer.h"

namespace ItemSystem
{
    /**
    *  @ingroup crafting
    *  @brief Responsible for crafting based on CraftingRequirements and CraftingResults
    */
    class CraftingRecipe
    {
    public:
        CraftingRecipe(const QJsonObject& jsonObject);
        ~CraftingRecipe();

        /**
        *  @brief Searches in the given ItemContainer for the required items and adds the crafted items.
        *
        * @param amount Specifies how often the recipe will be crafted
        * @return Returns true if crafting was successful, false otherwise
        */
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

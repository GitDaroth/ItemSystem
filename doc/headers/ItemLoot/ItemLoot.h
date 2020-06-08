/** @defgroup item_loot Item Loot
 *
 *  Item Loot can be defined by ItemLootLists which are designed in a JSON file.<br>
 *  An ItemLootList consists of multiple ItemLootSets and these consists of multiple ItemLoots.<br>
 *  <br>
 *  In the following JSON file are two ItemLootSets defined.<br>
 *  The first ItemLootSet drops with a 50% chance a common ingredient and with a 15% chance a random potion.<br>
 *  The second ItemLootSet drops with a 0.5% chance an Item with the tag "dragon_slayer".
 *  @code{.cpp}
 *  [
 *  	{"item_loot_list":{
 *  		"tag": "common_loot_list",
 *  		"item_loot_sets":[
 *  			{"item_loot_set":[
 *  				{"item_loot":{
 *  					"amount": 2,
 *  					"chance": 0.5,
 *  					"item_condition_chain":{
 *  						"operator": "and",
 *  						"chained_item_conditions":[
 *  							{"item_category_condition":{
 *  								"operator": "equal",
 *  								"value": "ingredient"
 *  							}},
 *  							{"item_rarity_condition":{
 *  								"operator": "equal",
 *  								"value": "common"
 *  							}}
 *  						]
 *  					}
 *  				}},
 *  				{"item_loot":{
 *  					"amount": 1,
 *  					"chance": 0.15,
 *  					"item_category_condition":{
 *  						"operator": "equal",
 *  						"value": "potion"
 *  					}
 *  				}}
 *  			]},
 *  			{"item_loot_set":[
 *  				{"item_loot":{
 *  					"amount": 1,
 *  					"chance": 0.005,
 *  					"item_tag_condition":{
 *  						"operator": "equal",
 *  						"value": "dragon_slayer"
 *  					}
 *  				}}
 *  			]}
 *  		]
 *  	}}
 *  ]
 *  @endcode
 *
 *  Example usage
 *  @code{.cpp}
 *  ItemLootListManager::getInstance()->readItemLootLists("itemLootLists.json");
 *  auto commonLootList = ItemLootListManager::getInstance()->getItemLootListByTag("common_loot_list");
 *  auto loot = commonLootList->createLoot();
 *  for(auto item : loot)
 *  	inventory->addItem(item);
 *  @endcode
 *
 *  <b>Character module</b><br>
 *  <img src="../images/loot_sw.png">
 */

#pragma once

#include "../ItemCondition/ItemCondition.h"
#include "../Item/Item.h"

#include <QRandomGenerator>

namespace ItemSystem
{
    /**
    *  @ingroup item_loot
    *  @brief Responsible for creating Items by a chance and an ItemCondition
    */
    class ItemLoot
    {
    public:
        ItemLoot(const QJsonObject& jsonObject);
        ~ItemLoot();

        /**
        *  @brief Creates the loot by randomly picking an ItemTemplate that matches the ItemCondition
        */
        QList<std::shared_ptr<Item>> createLoot();

        unsigned int getAmount() const;
        float getChance() const;

    private:
        void read(const QJsonObject& jsonObject);
        void readAmount(const QJsonObject& jsonObject);
        void readChance(const QJsonObject& jsonObject);
        void readItemCondition(const QJsonObject& jsonObject);

        unsigned int m_amount;
        float m_chance;
        std::shared_ptr<ItemCondition> m_itemCondition;
        QRandomGenerator m_randomGenerator;
    };
}

/** 
* @mainpage ItemSystemPackage 
* 
* This Package for the SGFramework provides interfaces to a flexible and extensible ItemSystem.<br>
* It supports the following topics:
* 
* <ul> 
* <li>items and extensible properties and effects</li>
* <li>effect system</li>
* <li>attribute system</li>
* <li>item container system and inventory</li>
* <li>crafting system</li>
* <li>loot system</li>
* <li>content creation with JSON files</li>
* </ul>
*
* In order to keep the ItemSystem updated you need to update all Characters and the EffectSystem in the game loop
* @code{.cpp}
* void Game::update(float deltaTime)
* {
*         for(auto character : m_gameCharacters)
*                 character->update(deltaTime);
*         EffectSystem::getInstance()->update(deltaTime);
*         ...
* }
* @endcode
*
* <b>Overview of the ItemSystemPackage</b><br>
* <img src="../images/item_system_package.png"> 
* 
* @author Fabian Gulde
*/ 

/** @defgroup item_group Item
 *
 *  Items consists of multiple ItemProperties in order to define its behaviour.<br>
 *  Common ItemProperties like StackableProp, ConsumableProp and EquipableProp are preimplemented.<br>
 *  ItemEffects are part of some ItemProperties. Some Effects are also preimplemented.<br>
 *  ItemProperties and ItemEffect may be freely extended by the user.<br>
 *  <br>
 *  The contents for the Items are designed within JSON files:
 *  @code{.cpp}
 *  [
 *  	{"item":{
 *  		"tag": "honey",
 *  		"name": "Honey",
 *  		"properties":[
 *  			{"category_prop":{
 *  				"category": "ingredient"
 *  			}},
 *  			{"rarity_prop":{
 *  				"rarity": "common"
 *  			}},
 *  			{"stackable_prop"{
 *  				"max_stacks": 99
 *  			}}
 *  		]
 *  	}}
 *
 *  	{"item":{
 *  		"tag": "rejuvenation_potion",
 *  		"name": "Rejuvenation Potion",
 *  		"properties":[
 *  			{"category_prop":{
 *  				"category": "potion"
 *  			}},
 *  			{"rarity_prop":{
 *  				"rarity": "magic"
 *  			}},
 *  			{"stackable_prop":{
 *  				"max_stacks": 99
 *  			}},
 *  			{"consumable_prop":{
 *  				"cooldown": 60,
 *  				"is_unlimited": false,
 *  				"effect_target_method": "item_owner",
 *  				"effects":[
 *  					{"over_time_effect":{
 *  						"duration": [10, 15],
 *  						"update_interval": 0.1,
 *  						"passive_effects":[
 *  							{"attribute_effect":{
 *  								"attribute_tag": "health",
 *  								"modifier_method": "additive",
 *  								"modifier_value": [200, 350]
 *  							}},
 *  							{"attribute_effect":{
 *  								"attribute_tag": "mana",
 *  								"modifier_method": "additive",
 *  								"modifier_value": 150
 *  							}}
 *  						]
 *  					}}
 *  				]
 *  			}}
 *  		]
 *  	}},
 *  	{"item":{
 *  		"tag": "dragon_slayer",
 *  		"name": "Dragon Slayer",
 *  		"properties":[
 *  			{"category_prop":{
 *  				"category": "weapon"
 *  			}},
 *  			{"rarity_prop":{
 *  				"rarity": "rare"
 *  			}},
 *  			{"equipable_prop":{
 *  				"passive_effects":[
 *  					{"attribute_effect":{
 *  						"attribute_tag": "attack_damage",
 *  						"modifier_method": "additive",
 *  						"modifier_value": [145, 255]
 *  					}},
 *  					{"attribute_effect":{
 *  						"attribute_tag": "max_health",
 *  						"modifier_method": "multiplicative",
 *  						"modifier_value": [0.1, 0.15]
 *  					}}
 *  				]
 *  			}}
 *  		]
 *  	}}
 *  ]
 *  @endcode
 *
 *  In order to read in the Items you first need to register the concrete ItemProperties and ItemEffects to the respective factory.<br>
 *  <b>This needs to be done BEFORE the items are read in.</b>
 *
 *  @code{.cpp}
 *  ItemPropertyFactory::registerType<StackableProp, StackablePropTemplate>("stackable_prop");
 *  ItemPropertyFactory::registerType<ConsumableProp, ConsumablePropTemplate>("consumable_prop");
 *  ItemPropertyFactory::registerType<EquipableProp, EquipablePropTemplate>("equipable_prop");
 *  ItemPropertyFactory::registerType<CategoryProp, CategoryPropTemplate>("category_prop");
 *  ItemPropertyFactory::registerType<RarityProp, RarityPropTemplate>("rarity_prop");
 *
 *  ItemEffectFactory::registerType<ItemAttributeEffect, ItemAttributeEffectTemplate>("attribute_effect");
 *  ItemEffectFactory::registerType<ItemOverTimeEffect, ItemOverTimeEffectTemplate>("over_time_effect");
 *  ItemEffectFactory::registerType<ItemTemporalEffect, ItemTemporalEffectTemplate>("temporal_effect");
 *  @endcode
 *
 *  Afterwards you may read the Items from the JSON file and instance Items by using the ItemFactory
 *
 *  @code{.cpp}
 *  ItemTemplateManager::getInstance()->readItemTemplates("items.json");
 *  auto dragonSlayerItem = ItemFactory::createItem("dragon_slayer");
 *  @endcode
 *
 *  <b>Item module</b><br>
 *  <img src="../images/item_prop_complete.png">
 */ 

#pragma once

#include "ItemTemplate.h"
#include "../Effect/EffectTarget.h"

namespace ItemSystem
{
    class ItemProperty;

    /**
    *  @ingroup item_group
    *  @brief Item is basically a container of ItemProperties and is a type object of ItemTemplate
    */
    class Item : public EffectTarget, public std::enable_shared_from_this<Item>
    {
    public:
        Item(const unsigned int instanceId, std::shared_ptr<ItemTemplate> itemTemplate);
        ~Item();

        void initialize();
        void initialize(std::shared_ptr<Item> itemToBeCopied);
        virtual void update(float deltaTime) override;

        QString getTag() const;
        QString getName() const;
        unsigned int getId() const;
        const QList<std::shared_ptr<ItemProperty>>& getProperties() const;
        std::shared_ptr<ItemTemplate> getTemplate();

        template<typename PropertyType>
        bool hasProperty() const
        {
            static_assert(std::is_base_of<ItemProperty, PropertyType>::value, "PropertyType must inherit from ItemProperty!");
            for (std::shared_ptr<ItemProperty> property : m_properties)
            {
                if (std::dynamic_pointer_cast<PropertyType>(property))
                    return true;
            }
            return false;
        }

        template<typename PropertyType>
        std::shared_ptr<PropertyType> getProperty()
        {
            static_assert(std::is_base_of<ItemProperty, PropertyType>::value, "PropertyType must inherit from ItemProperty!");
            for (std::shared_ptr<ItemProperty> property : m_properties)
            {
                if (std::dynamic_pointer_cast<PropertyType>(property))
                    return std::dynamic_pointer_cast<PropertyType>(property);
            }
            return nullptr;
        }

    protected:
        const unsigned int m_instanceId;
        std::shared_ptr<ItemTemplate> m_template;
        QList<std::shared_ptr<ItemProperty>> m_properties;
    };
}

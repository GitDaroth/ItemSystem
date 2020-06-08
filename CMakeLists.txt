cmake_minimum_required(VERSION 3.17)

project(ItemSystem VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(attributeFiles
	Attribute/Attribute.h
	Attribute/Attribute.cpp
	Attribute/AttributeSystem.h
	Attribute/AttributeSystem.cpp
	Attribute/ResourceAttribute.h
	Attribute/ResourceAttribute.cpp
	Attribute/TraitAttribute.h
	Attribute/TraitAttribute.cpp)

set(characterFiles
	Character/Character.h
	Character/Character.cpp
	Character/CharacterComponent.h
	Character/CharacterComponent.cpp)

set(craftingFiles
	Crafting/CraftingRecipe.h
	Crafting/CraftingRecipe.cpp
	Crafting/CraftingRecipeManager.h
	Crafting/CraftingRecipeManager.cpp
	Crafting/CraftingRequirement.h
	Crafting/CraftingRequirement.cpp
	Crafting/CraftingResult.h
	Crafting/CraftingResult.cpp)

set(effectFiles
	Effect/AttributeEffect.h
	Effect/AttributeEffect.cpp
	Effect/Effect.h
	Effect/Effect.cpp
	Effect/EffectSystem.h
	Effect/EffectSystem.cpp
	Effect/EffectTarget.h
	Effect/OverTimeEffect.h
	Effect/OverTimeEffect.cpp
	Effect/PassiveEffect.h
	Effect/PassiveEffect.cpp
	Effect/TemporalEffect.h
	Effect/TemporalEffect.cpp
	Effect/TimedEffect.h
	Effect/TimedEffect.cpp)

set(itemFiles
	Item/Item.h
	Item/Item.cpp
	Item/ItemFactory.h
	Item/ItemFactory.cpp
	Item/ItemTemplate.h
	Item/ItemTemplate.cpp
	Item/ItemTemplateManager.h
	Item/ItemTemplateManager.cpp
	Item/Template.h)

set(itemEffectFiles
	Item/ItemEffect/ItemAttributeEffect.h
	Item/ItemEffect/ItemAttributeEffect.cpp
	Item/ItemEffect/ItemAttributeEffectTemplate.h
	Item/ItemEffect/ItemAttributeEffectTemplate.cpp
	Item/ItemEffect/ItemEffect.h
	Item/ItemEffect/ItemEffect.cpp
	Item/ItemEffect/ItemEffectFactory.h
	Item/ItemEffect/ItemEffectFactory.cpp
	Item/ItemEffect/ItemEffectTemplate.h
	Item/ItemEffect/ItemEffectTemplate.cpp
	Item/ItemEffect/ItemOverTimeEffect.h
	Item/ItemEffect/ItemOverTimeEffect.cpp
	Item/ItemEffect/ItemOverTimeEffectTemplate.h
	Item/ItemEffect/ItemOverTimeEffectTemplate.cpp
	Item/ItemEffect/ItemPassiveEffect.h
	Item/ItemEffect/ItemPassiveEffect.cpp
	Item/ItemEffect/ItemPassiveEffectTemplate.h
	Item/ItemEffect/ItemPassiveEffectTemplate.cpp
	Item/ItemEffect/ItemTemporalEffect.h
	Item/ItemEffect/ItemTemporalEffect.cpp
	Item/ItemEffect/ItemTemporalEffectTemplate.h
	Item/ItemEffect/ItemTemporalEffectTemplate.cpp
	Item/ItemEffect/ItemTimedEffect.h
	Item/ItemEffect/ItemTimedEffect.cpp
	Item/ItemEffect/ItemTimedEffectTemplate.h
	Item/ItemEffect/ItemTimedEffectTemplate.cpp)

set(itemPropertyFiles
	Item/ItemProperty/ConsumableProp.h
	Item/ItemProperty/ConsumableProp.cpp
	Item/ItemProperty/ConsumablePropTemplate.h
	Item/ItemProperty/ConsumablePropTemplate.cpp
	Item/ItemProperty/EquipableProp.h
	Item/ItemProperty/EquipableProp.cpp
	Item/ItemProperty/EquipablePropTemplate.h
	Item/ItemProperty/EquipablePropTemplate.cpp
	Item/ItemProperty/ItemProperty.h
	Item/ItemProperty/ItemProperty.cpp
	Item/ItemProperty/ItemPropertyFactory.h
	Item/ItemProperty/ItemPropertyFactory.cpp
	Item/ItemProperty/ItemPropertyTemplate.h
	Item/ItemProperty/ItemPropertyTemplate.cpp
	Item/ItemProperty/StackableProp.h
	Item/ItemProperty/StackableProp.cpp
	Item/ItemProperty/StackablePropTemplate.h
	Item/ItemProperty/StackablePropTemplate.cpp)

set(itemConditionFiles
	ItemCondition/ItemCondition.h
	ItemCondition/ItemCondition.cpp
	ItemCondition/ItemConditionChain.h
	ItemCondition/ItemConditionChain.cpp
	ItemCondition/ItemConditionFactory.h
	ItemCondition/ItemConditionFactory.cpp
	ItemCondition/ItemIntegerCondition.h
	ItemCondition/ItemIntegerCondition.cpp
	ItemCondition/ItemNullCondition.h
	ItemCondition/ItemNullCondition.cpp
	ItemCondition/ItemStringCondition.h
	ItemCondition/ItemStringCondition.cpp
	ItemCondition/ItemTagCondition.h
	ItemCondition/ItemTagCondition.cpp)

set(itemContainerFiles
	ItemContainer/EquipmentSlot.h
	ItemContainer/EquipmentSlot.cpp
	ItemContainer/ItemContainer.h
	ItemContainer/ItemContainer.cpp
	ItemContainer/ItemInventory.h
	ItemContainer/ItemInventory.cpp)

set(itemLootFiles
	ItemLoot/ItemLoot.h
	ItemLoot/ItemLoot.cpp
	ItemLoot/ItemLootList.h
	ItemLoot/ItemLootList.cpp
	ItemLoot/ItemLootListManager.h
	ItemLoot/ItemLootListManager.cpp
	ItemLoot/ItemLootSet.h
	ItemLoot/ItemLootSet.cpp)

add_library(ItemSystem STATIC 
	${attributeFiles}
	${characterFiles} 
	${craftingFiles} 
	${effectFiles} 
	${itemFiles} 
	${itemEffectFiles} 
	${itemPropertyFiles}
	${itemConditionFiles}
	${itemContainerFiles}
	${itemLootFiles})

source_group("\\Attribute" FILES ${attributeFiles})
source_group("\\Character" FILES ${characterFiles})
source_group("\\Crafting" FILES ${craftingFiles})
source_group("\\Effect" FILES ${effectFiles})
source_group("\\Item" FILES ${itemFiles})
source_group("\\Item\\ItemEffect" FILES ${itemEffectFiles})
source_group("\\Item\\ItemProperty" FILES ${itemPropertyFiles})
source_group("\\ItemCondition" FILES ${itemConditionFiles})
source_group("\\ItemContainer" FILES ${itemContainerFiles})
source_group("\\ItemLoot" FILES ${itemLootFiles})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core REQUIRED)

target_link_libraries(ItemSystem PUBLIC Qt5::Core)
target_include_directories(ItemSystem PUBLIC "")
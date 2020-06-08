/** @defgroup item_condition Item Condition
 *
 *  ItemConditions are used to check if an ItemTemplate matches a certain condition.<br>
 *  They are used in various places (ex. EquipmentSlot, ItemLoot, CraftingRecipe) and can be extended through inheritance.<br>
 *  Before reading in content that relies on ItemConditions you need to register the concrete ItemConditions to the respective factory.
 *
 *  @code{.cpp}
 *  ItemConditionFactory::registerType<ItemNullCondition>("item_null_condition");
 *  ItemConditionFactory::registerType<ItemConditionChain>("item_condition_chain");
 *  ItemConditionFactory::registerType<ItemTagCondition>("item_tag_condition");
 *  ItemConditionFactory::registerType<ItemCategoryCondition>("item_category_condition");
 *  ItemConditionFactory::registerType<ItemRarityCondition>("item_rarity_condition");
 *  @endcode
 *
 *  <b>ItemCondition module</b><br>
 *  <img src="../images/item_conditions_sw.png">
 */

#pragma once

#include "../Item/ItemTemplate.h"

#include <functional>

namespace ItemSystem
{
    /**
    *  @ingroup item_condition
    *  @brief Used to specify a condition that an ItemTemplate must satisfy
    */
    class ItemCondition
    {
    public:
        ItemCondition(const QString& typeTag);
        virtual ~ItemCondition();

        void read(const QJsonObject& conditionJsonObject);
        virtual void onRead(const QJsonObject& conditionJsonObject) = 0;
        /**
        *  @brief Pure virtual method to check if the given ItemTemplate matches the ItemCondition
        */
        virtual bool evaluate(std::shared_ptr<ItemTemplate> itemTemplate) = 0;

        QString getTypeTag() const;

    protected:
        virtual void initOperatorFunction() = 0;

        QString m_typeTag;
        QString m_operator;

    private:
        void readOperator(const QJsonObject& conditionJsonObject);
    };
}

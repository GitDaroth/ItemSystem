#pragma once

#include "ItemCondition.h"

#include <QMap>

namespace ItemSystem
{
    /**
    *  @ingroup item_condition
    *  @brief Responsible for creating and registering ItemConditions
    */
    class ItemConditionFactory
    {
    public:
        static std::shared_ptr<ItemCondition> createItemCondition(const QString& conditionTypeTag, const QJsonObject& jsonObject);

        /**
        *  @brief Registers a concrete ItemCondition class with a type tag referencing the ItemCondition in the JSON-File
        */
        template<typename ConditionType>
        static void registerType(const QString& conditionTypeTag)
        {
            static_assert(std::is_base_of<ItemCondition, ConditionType>::value, "ConditionType must inherit from ItemCondition!");
            m_conditionConstructors[conditionTypeTag] = &instantiateItemCondition<ConditionType>;
        }

    private:
        static bool isItemConditionTypeRegistered(const QString& conditionTypeTag);

        template<typename ConditionType>
        static std::shared_ptr<ItemCondition> instantiateItemCondition(const QString& conditionTypeTag)
        {
            static_assert(std::is_base_of<ItemCondition, ConditionType>::value, "ConditionType must inherit from ItemCondition!");
            return std::make_shared<ConditionType>(conditionTypeTag);
        }

        static QMap<QString, std::shared_ptr<ItemCondition>(*)(const QString&)> m_conditionConstructors;
    };
}

#pragma once

#include "ItemStringCondition.h"

namespace ItemSystem
{
    /**
    *  @ingroup item_condition
    *  @brief Handles comparisons with the tag of an ItemTemplate
    */
    class ItemTagCondition : public ItemStringCondition
    {
    public:
        ItemTagCondition(const QString& typeTag);
        ~ItemTagCondition();

        bool evaluate(std::shared_ptr<ItemTemplate> itemTemplate) override;
    };
}

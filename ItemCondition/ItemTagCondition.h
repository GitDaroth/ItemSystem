#pragma once

#include "ItemStringCondition.h"

namespace ItemSystem
{
    class ItemTagCondition : public ItemStringCondition
    {
    public:
        ItemTagCondition(const QString& typeTag);
        ~ItemTagCondition();

        bool evaluate(std::shared_ptr<ItemTemplate> itemTemplate) override;
    };
}

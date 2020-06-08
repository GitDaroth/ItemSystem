#include "ItemTagCondition.h"

namespace ItemSystem
{
    ItemTagCondition::ItemTagCondition(const QString& typeTag) :
        ItemStringCondition(typeTag)
    {
    }

    ItemTagCondition::~ItemTagCondition()
    {
    }

    bool ItemTagCondition::evaluate(std::shared_ptr<ItemTemplate> itemTemplate)
    {
        return m_operatorFunction(itemTemplate->getTag(), m_value);
    }
}

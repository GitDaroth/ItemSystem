#include "ItemNullCondition.h"

namespace ItemSystem
{
    ItemNullCondition::ItemNullCondition(const QString& typeTag) :
        ItemCondition(typeTag)
    {
    }

    ItemNullCondition::~ItemNullCondition()
    {
    }

    void ItemNullCondition::onRead(const QJsonObject& conditionJsonObject)
    {
    }

    bool ItemNullCondition::evaluate(std::shared_ptr<ItemTemplate> itemTemplate)
    {
        return true;
    }

    void ItemNullCondition::initOperatorFunction()
    {
    }
}

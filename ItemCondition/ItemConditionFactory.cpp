#include "ItemConditionFactory.h"

#include <QtGlobal>

namespace ItemSystem
{
    QMap<QString, std::shared_ptr<ItemCondition>(*)(const QString&)> ItemConditionFactory::m_conditionConstructors;

    std::shared_ptr<ItemCondition> ItemConditionFactory::createItemCondition(const QString& conditionTypeTag, const QJsonObject& jsonObject)
    {
        Q_ASSERT(isItemConditionTypeRegistered(conditionTypeTag));
        auto constructCondition = m_conditionConstructors[conditionTypeTag];
        std::shared_ptr<ItemCondition> itemCondition = constructCondition(conditionTypeTag);
        itemCondition->read(jsonObject);
        return itemCondition;
    }

    bool ItemConditionFactory::isItemConditionTypeRegistered(const QString& conditionTypeTag)
    {
        return m_conditionConstructors.contains(conditionTypeTag);
    }
}

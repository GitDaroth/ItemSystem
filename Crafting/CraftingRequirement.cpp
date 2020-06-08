#include "CraftingRequirement.h"

#include "../ItemCondition/ItemConditionFactory.h"

#include <QtGlobal>

namespace ItemSystem
{
    CraftingRequirement::CraftingRequirement(const QJsonObject& jsonObject)
    {
        read(jsonObject);
    }

    CraftingRequirement::~CraftingRequirement()
    {
    }

    bool CraftingRequirement::check(std::shared_ptr<Item> item) const
    {
        return m_itemCondition->evaluate(item->getTemplate());
    }

    void CraftingRequirement::read(const QJsonObject& jsonObject)
    {
        readAmount(jsonObject);
        readItemCondition(jsonObject);
    }

    void CraftingRequirement::readAmount(const QJsonObject& jsonObject)
    {
        QJsonValue amountJsonValue = jsonObject.value("amount");
        Q_ASSERT(amountJsonValue.isDouble());
        Q_ASSERT((int)amountJsonValue.toDouble() > 0);
        m_amount = (unsigned int)amountJsonValue.toDouble();
    }

    void CraftingRequirement::readItemCondition(const QJsonObject& jsonObject)
    {
        Q_ASSERT(jsonObject.keys().size() == 2);

        QString itemConditionType;
        for(QString key : jsonObject.keys())
        {
            if(key != "amount")
                itemConditionType = key;
        }

        QJsonValue itemConditionJsonValue = jsonObject.value(itemConditionType);
        Q_ASSERT(itemConditionJsonValue.isObject());
        QJsonObject itemConditionJsonObject = itemConditionJsonValue.toObject();

        m_itemCondition = ItemConditionFactory::createItemCondition(itemConditionType, itemConditionJsonObject);
    }

    unsigned int CraftingRequirement::getAmount() const
    {
        return m_amount;
    }
}

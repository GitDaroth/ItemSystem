#include "ItemConditionChain.h"

#include "ItemConditionFactory.h"

#include <QtGlobal>
#include <QJsonArray>
#include <QJsonValue>

namespace ItemSystem
{
    ItemConditionChain::ItemConditionChain(const QString& typeTag) :
        ItemCondition(typeTag)
    {
    }

    ItemConditionChain::~ItemConditionChain()
    {
    }

    bool ItemConditionChain::evaluate(std::shared_ptr<ItemTemplate> itemTemplate)
    {
        bool evaluationResult = true;
        for (auto condition : m_chainedConditions)
        {
            evaluationResult = m_operatorFunction(evaluationResult, condition->evaluate(itemTemplate));
        }
        return evaluationResult;
    }

    void ItemConditionChain::initOperatorFunction()
    {
        if (m_operator == "and")
            m_operatorFunction = [](bool a, bool b) { return a && b; };
        else if (m_operator == "or")
            m_operatorFunction = [](bool a, bool b) { return a || b; };
        else
            m_operatorFunction = [](bool a, bool b) { return false; };
    }

    void ItemConditionChain::onRead(const QJsonObject& conditionJsonObject)
    {
        readChainedConditions(conditionJsonObject);
    }

    void ItemConditionChain::readChainedConditions(const QJsonObject& conditionJsonObject)
    {
        QJsonValue chainedConditionsJsonValue = conditionJsonObject.value("chained_item_conditions");
        Q_ASSERT(chainedConditionsJsonValue.isArray());
        QJsonArray chainedConditionsJsonArray = chainedConditionsJsonValue.toArray();
        Q_ASSERT(chainedConditionsJsonArray.size() >= 2);
        for (QJsonValue chainedConditionWrapperJsonValue : chainedConditionsJsonArray)
        {
            Q_ASSERT(chainedConditionWrapperJsonValue.isObject());
            QJsonObject chainedConditionWrapperJsonObject = chainedConditionWrapperJsonValue.toObject();

            QString chainedConditionTypeTag = chainedConditionWrapperJsonObject.keys().first();

            QJsonValue chainedConditionJsonValue = chainedConditionWrapperJsonObject.value(chainedConditionTypeTag);
            Q_ASSERT(chainedConditionJsonValue.isObject());
            QJsonObject chainedConditionJsonObject = chainedConditionJsonValue.toObject();

            std::shared_ptr<ItemCondition> chainedCondition = ItemConditionFactory::createItemCondition(chainedConditionTypeTag, chainedConditionJsonObject);
            m_chainedConditions.append(chainedCondition);
        }
    }
}

#include "ItemIntegerCondition.h"

#include <QtGlobal>

namespace ItemSystem
{
    ItemIntegerCondition::ItemIntegerCondition(const QString& typeTag) :
        ItemCondition(typeTag)
    {
    }

    ItemIntegerCondition::~ItemIntegerCondition()
    {
    }

    void ItemIntegerCondition::onRead(const QJsonObject& conditionJsonObject)
    {
        readValue(conditionJsonObject);
    }

    void ItemIntegerCondition::initOperatorFunction()
    {
        if (m_operator == "equal")
            m_operatorFunction = [](int a, int b) { return a == b; };
        else if (m_operator == "not_equal")
            m_operatorFunction = [](int a, int b) { return a != b; };
        else if (m_operator == "less")
            m_operatorFunction = [](int a, int b) { return a < b; };
        else if (m_operator == "less_equal")
            m_operatorFunction = [](int a, int b) { return a <= b; };
        else if (m_operator == "greater")
            m_operatorFunction = [](int a, int b) { return a > b; };
        else if (m_operator == "greater_equal")
            m_operatorFunction = [](int a, int b) { return a >= b; };
        else
            m_operatorFunction = [](int a, int b) { return false; };
    }

    void ItemIntegerCondition::readValue(const QJsonObject& conditionJsonObject)
    {
        QJsonValue valueJsonValue = conditionJsonObject.value("value");
        Q_ASSERT(valueJsonValue.isDouble());
        m_value = (int)valueJsonValue.toDouble();
    }
}

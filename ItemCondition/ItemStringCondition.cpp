#include "ItemStringCondition.h"

#include <QtGlobal>

namespace ItemSystem
{
    ItemStringCondition::ItemStringCondition(const QString& typeTag) :
        ItemCondition(typeTag)
    {
    }

    ItemStringCondition::~ItemStringCondition()
    {
    }

    void ItemStringCondition::onRead(const QJsonObject& conditionJsonObject)
    {
        readValue(conditionJsonObject);
    }

    void ItemStringCondition::initOperatorFunction()
    {
        if (m_operator == "equal")
            m_operatorFunction = [](QString a, QString b) { return a == b; };
        else if (m_operator == "not_equal")
            m_operatorFunction = [](QString a, QString b) { return a != b; };
        else
            m_operatorFunction = [](QString a, QString b) { return false; };
    }

    void ItemStringCondition::readValue(const QJsonObject& conditionJsonObject)
    {
        QJsonValue valueJsonValue = conditionJsonObject.value("value");
        Q_ASSERT(valueJsonValue.isString());
        m_value = valueJsonValue.toString();
    }
}

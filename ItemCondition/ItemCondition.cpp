#include "ItemCondition.h"

#include <QtGlobal>

namespace ItemSystem
{
    ItemCondition::ItemCondition(const QString& typeTag) :
        m_typeTag(typeTag)
    {
    }

    ItemCondition::~ItemCondition()
    {
    }

    void ItemCondition::read(const QJsonObject& conditionJsonObject)
    {
        readOperator(conditionJsonObject);
        onRead(conditionJsonObject);
        initOperatorFunction();
    }

    void ItemCondition::readOperator(const QJsonObject& conditionJsonObject)
    {
        QJsonValue operatorJsonValue = conditionJsonObject.value("operator");
        Q_ASSERT(operatorJsonValue.isString());
        m_operator = operatorJsonValue.toString();
    }

    QString ItemCondition::getTypeTag() const
    {
        return m_typeTag;
    }
}

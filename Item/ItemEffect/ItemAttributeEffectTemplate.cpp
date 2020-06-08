#include "ItemAttributeEffectTemplate.h"

#include <QJsonArray>

namespace ItemSystem
{
    ItemAttributeEffectTemplate::ItemAttributeEffectTemplate(const QString& typeTag) :
        ItemPassiveEffectTemplate(typeTag)
    {
    }

    ItemAttributeEffectTemplate::~ItemAttributeEffectTemplate()
    {
    }

    void ItemAttributeEffectTemplate::read(const QJsonObject& jsonObject)
    {
        readAttributeTag(jsonObject);
        readModifierMethod(jsonObject);
        readModifierValue(jsonObject);
    }

    void ItemAttributeEffectTemplate::readAttributeTag(const QJsonObject& jsonObject)
    {
        QJsonValue attributeTagJsonValue = jsonObject.value("attribute_tag");
        Q_ASSERT(attributeTagJsonValue.isString());
        m_attributeTag = attributeTagJsonValue.toString();
    }

    void ItemAttributeEffectTemplate::readModifierMethod(const QJsonObject& jsonObject)
    {
        QJsonValue modifierMethodJsonValue = jsonObject.value("modifier_method");
        Q_ASSERT(modifierMethodJsonValue.isString());
        m_modifierMethod = modifierMethodJsonValue.toString();
    }

    void ItemAttributeEffectTemplate::readModifierValue(const QJsonObject& jsonObject)
    {
        QJsonValue modifierValueJsonValue = jsonObject.value("modifier_value");
        Q_ASSERT(modifierValueJsonValue.isDouble() || modifierValueJsonValue.isArray());
        if (modifierValueJsonValue.isDouble())
        {
            float modifierValue = (float)modifierValueJsonValue.toDouble();
            m_minModifierValue = modifierValue;
            m_maxModifierValue = modifierValue;
        }
        else if (modifierValueJsonValue.isArray())
        {
            QJsonArray modifierValueJsonArray = modifierValueJsonValue.toArray();
            Q_ASSERT(modifierValueJsonArray.size() == 2);

            QJsonValue modifierFirstValueJsonValue = modifierValueJsonArray.at(0);
            Q_ASSERT(modifierFirstValueJsonValue.isDouble());
            float modifierFirstValue = (float)modifierFirstValueJsonValue.toDouble();

            QJsonValue modifierSecondValueJsonValue = modifierValueJsonArray.at(1);
            Q_ASSERT(modifierSecondValueJsonValue.isDouble());
            float modifierSecondValue = (float)modifierSecondValueJsonValue.toDouble();

            if (modifierFirstValue <= modifierSecondValue)
            {
                m_minModifierValue = modifierFirstValue;
                m_maxModifierValue = modifierSecondValue;
            }
            else
            {
                m_minModifierValue = modifierSecondValue;
                m_maxModifierValue = modifierFirstValue;
            }
        }
    }

    QString ItemAttributeEffectTemplate::getAttributeTag() const
    {
        return m_attributeTag;
    }

    QString ItemAttributeEffectTemplate::getModifierMethod() const
    {
        return m_modifierMethod;
    }

    float ItemAttributeEffectTemplate::getMinModifierValue() const
    {
        return m_minModifierValue;
    }

    float ItemAttributeEffectTemplate::getMaxModifierValue() const
    {
        return m_maxModifierValue;
    }
}

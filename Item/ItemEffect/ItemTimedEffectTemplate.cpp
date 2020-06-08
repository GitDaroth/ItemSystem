#include "ItemTimedEffectTemplate.h"

#include "ItemEffectFactory.h"

#include <QJsonArray>

namespace ItemSystem
{
    ItemTimedEffectTemplate::ItemTimedEffectTemplate(const QString& typeTag) :
        ItemEffectTemplate(typeTag)
    {
    }

    ItemTimedEffectTemplate::~ItemTimedEffectTemplate()
    {
    }

    void ItemTimedEffectTemplate::read(const QJsonObject& jsonObject)
    {
        readDuration(jsonObject);
        readPassiveEffects(jsonObject);
        onRead(jsonObject);
    }

    void ItemTimedEffectTemplate::readDuration(const QJsonObject& jsonObject)
    {
        QJsonValue durationJsonValue = jsonObject.value("duration");
        Q_ASSERT(durationJsonValue.isDouble() || durationJsonValue.isArray());
        if (durationJsonValue.isDouble())
        {
            float duration = (float)durationJsonValue.toDouble();
            m_minDuration = duration;
            m_maxDuration = duration;
        }
        else if (durationJsonValue.isArray())
        {
            QJsonArray durationJsonArray = durationJsonValue.toArray();
            Q_ASSERT(durationJsonArray.size() == 2);

            QJsonValue durationFirstValueJsonValue = durationJsonArray.at(0);
            Q_ASSERT(durationFirstValueJsonValue.isDouble());
            float durationFirstValue = (float)durationFirstValueJsonValue.toDouble();

            QJsonValue durationSecondValueJsonValue = durationJsonArray.at(1);
            Q_ASSERT(durationSecondValueJsonValue.isDouble());
            float durationSecondValue = (float)durationSecondValueJsonValue.toDouble();

            if (durationFirstValue <= durationSecondValue)
            {
                m_minDuration = durationFirstValue;
                m_maxDuration = durationSecondValue;
            }
            else
            {
                m_minDuration = durationSecondValue;
                m_maxDuration = durationFirstValue;
            }
        }
    }

    void ItemTimedEffectTemplate::readPassiveEffects(const QJsonObject& jsonObject)
    {
        QJsonValue passiveEffectsJsonValue = jsonObject.value("passive_effects");
        Q_ASSERT(passiveEffectsJsonValue.isArray());
        QJsonArray passiveEffectsJsonArray = passiveEffectsJsonValue.toArray();
        for (QJsonValue passiveEffectWrapperJsonValue : passiveEffectsJsonArray)
        {
            Q_ASSERT(passiveEffectWrapperJsonValue.isObject());
            QJsonObject passiveEffectWrapperJsonObject = passiveEffectWrapperJsonValue.toObject();
            readPassiveEffect(passiveEffectWrapperJsonObject);
        }
    }

    void ItemTimedEffectTemplate::readPassiveEffect(const QJsonObject& passiveEffectWrapperJsonObject)
    {
        QString passiveEffectTypeTag = passiveEffectWrapperJsonObject.keys().first();

        QJsonValue passiveEffectJsonValue = passiveEffectWrapperJsonObject.value(passiveEffectTypeTag);
        Q_ASSERT(passiveEffectJsonValue.isObject());
        QJsonObject passiveEffectJsonObject = passiveEffectJsonValue.toObject();

        auto itemPassiveEffectTemplate = ItemEffectFactory::createItemEffectTemplate(passiveEffectTypeTag, passiveEffectJsonObject);
        Q_ASSERT(std::dynamic_pointer_cast<ItemPassiveEffectTemplate>(itemPassiveEffectTemplate));
        m_itemPassiveEffectTemplates.append(std::dynamic_pointer_cast<ItemPassiveEffectTemplate>(itemPassiveEffectTemplate));
    }

    const QList<std::shared_ptr<ItemPassiveEffectTemplate>>& ItemTimedEffectTemplate::getItemPassiveEffectTemplates()
    {
        return m_itemPassiveEffectTemplates;
    }

    float ItemTimedEffectTemplate::getMinDuration() const
    {
        return m_minDuration;
    }

    float ItemTimedEffectTemplate::getMaxDuration() const
    {
        return m_maxDuration;
    }
}

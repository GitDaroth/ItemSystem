#include "ConsumablePropTemplate.h"

#include "../ItemEffect/ItemEffectFactory.h"

#include <QJsonArray>
#include <QtGlobal>

namespace ItemSystem
{
    ConsumablePropTemplate::ConsumablePropTemplate(const QString& typeTag) :
        ItemPropertyTemplate(typeTag)
    {
    }

    ConsumablePropTemplate::~ConsumablePropTemplate()
    {
    }

    void ConsumablePropTemplate::read(const QJsonObject& jsonObject)
    {
        readCooldown(jsonObject);
        readIsUnlimited(jsonObject);
        readEffectTargetMethod(jsonObject);
        readItemEffects(jsonObject);
    }

    void ConsumablePropTemplate::readCooldown(const QJsonObject& jsonObject)
    {
        QJsonValue cooldownJsonValue = jsonObject.value("cooldown");
        Q_ASSERT(cooldownJsonValue.isDouble());
        Q_ASSERT(cooldownJsonValue.toDouble() >= 0.f);
        m_cooldown = (float)cooldownJsonValue.toDouble();
    }

    void ConsumablePropTemplate::readIsUnlimited(const QJsonObject& jsonObject)
    {
        QJsonValue isUnlimitedJsonValue = jsonObject.value("is_unlimited");
        Q_ASSERT(isUnlimitedJsonValue.isBool());
        m_isUnlimited = isUnlimitedJsonValue.toBool();
    }

    void ConsumablePropTemplate::readEffectTargetMethod(const QJsonObject& jsonObject)
    {
        QJsonValue targetMethodJsonValue = jsonObject.value("effect_target_method");
        Q_ASSERT(targetMethodJsonValue.isString());
        m_effectTargetMethod = targetMethodJsonValue.toString();
    }

    void ConsumablePropTemplate::readItemEffects(const QJsonObject& jsonObject)
    {
        QJsonValue effectsJsonValue = jsonObject.value("effects");
        Q_ASSERT(effectsJsonValue.isArray());
        QJsonArray effectsJsonArray = effectsJsonValue.toArray();
        for (QJsonValue effectWrapperJsonValue : effectsJsonArray)
        {
            Q_ASSERT(effectWrapperJsonValue.isObject());
            QJsonObject effectWrapperJsonObject = effectWrapperJsonValue.toObject();
            readItemEffect(effectWrapperJsonObject);
        }
    }

    void ConsumablePropTemplate::readItemEffect(const QJsonObject& effectWrapperJsonObject)
    {
        QString effectTypeTag = effectWrapperJsonObject.keys().first();

        QJsonValue effectJsonValue = effectWrapperJsonObject.value(effectTypeTag);
        Q_ASSERT(effectJsonValue.isObject());
        QJsonObject effectJsonObject = effectJsonValue.toObject();

        auto itemEffectTemplate = ItemEffectFactory::createItemEffectTemplate(effectTypeTag, effectJsonObject);
        m_itemEffectTemplates.append(itemEffectTemplate);
    }

    float ConsumablePropTemplate::getCooldown() const
    {
        return m_cooldown;
    }

    bool ConsumablePropTemplate::isUnlimited() const
    {
        return m_isUnlimited;
    }

    QString ConsumablePropTemplate::getEffectTargetMethod() const
    {
        return m_effectTargetMethod;
    }

    const QList<std::shared_ptr<ItemEffectTemplate>>& ConsumablePropTemplate::getItemEffectTemplates()
    {
        return m_itemEffectTemplates;
    }
}

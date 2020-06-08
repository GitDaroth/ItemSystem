#include "EquipablePropTemplate.h"

#include "../ItemEffect/ItemEffectFactory.h"

#include <QJsonArray>
#include <QtGlobal>

namespace ItemSystem
{
    EquipablePropTemplate::EquipablePropTemplate(const QString& typeTag) :
        ItemPropertyTemplate(typeTag)
    {
    }

    EquipablePropTemplate::~EquipablePropTemplate()
    {
    }

    void EquipablePropTemplate::read(const QJsonObject& jsonObject)
    {
        readItemPassiveEffects(jsonObject);
    }

    void EquipablePropTemplate::readItemPassiveEffects(const QJsonObject& jsonObject)
    {
        QJsonValue passiveEffectsJsonValue = jsonObject.value("passive_effects");
        Q_ASSERT(passiveEffectsJsonValue.isArray());
        QJsonArray passiveEffectsJsonArray = passiveEffectsJsonValue.toArray();
        for (QJsonValue passiveEffectWrapperJsonValue : passiveEffectsJsonArray)
        {
            Q_ASSERT(passiveEffectWrapperJsonValue.isObject());
            QJsonObject passiveEffectWrapperJsonObject = passiveEffectWrapperJsonValue.toObject();
            readItemPassiveEffect(passiveEffectWrapperJsonObject);
        }
    }

    void EquipablePropTemplate::readItemPassiveEffect(const QJsonObject& passiveEffectWrapperJsonObject)
    {
        QString passiveEffectTypeTag = passiveEffectWrapperJsonObject.keys().first();

        QJsonValue passiveEffectJsonValue = passiveEffectWrapperJsonObject.value(passiveEffectTypeTag);
        Q_ASSERT(passiveEffectJsonValue.isObject());
        QJsonObject passiveEffectJsonObject = passiveEffectJsonValue.toObject();

        auto itemPassiveEffectTemplate = ItemEffectFactory::createItemEffectTemplate(passiveEffectTypeTag, passiveEffectJsonObject);
        Q_ASSERT(std::dynamic_pointer_cast<ItemPassiveEffectTemplate>(itemPassiveEffectTemplate));
        m_itemPassiveEffectTemplates.append(std::dynamic_pointer_cast<ItemPassiveEffectTemplate>(itemPassiveEffectTemplate));
    }

    const QList<std::shared_ptr<ItemPassiveEffectTemplate>>& EquipablePropTemplate::getItemPassiveEffectTemplates()
    {
        return m_itemPassiveEffectTemplates;
    }
}

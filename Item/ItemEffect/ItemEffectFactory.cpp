#include "ItemEffectFactory.h"

#include <QtGlobal>

namespace ItemSystem
{
    QMap<QString, std::shared_ptr<ItemEffect>(*)(std::shared_ptr<ItemEffectTemplate>)> ItemEffectFactory::m_effectConstructors;
    QMap<QString, std::shared_ptr<ItemEffectTemplate>(*)(const QString&)> ItemEffectFactory::m_effectTemplateConstructors;

    std::shared_ptr<ItemEffect> ItemEffectFactory::createItemEffect(std::shared_ptr<ItemEffectTemplate> effectTemplate)
    {
        Q_CHECK_PTR(effectTemplate);
        QString effectTypeTag = effectTemplate->getTypeTag();

        Q_ASSERT(isItemEffectTypeRegistered(effectTypeTag));
        auto constructEffect = m_effectConstructors[effectTypeTag];
        std::shared_ptr<ItemEffect> effect = constructEffect(effectTemplate);
        effect->randomize();
        return effect;
    }

    std::shared_ptr<ItemEffectTemplate> ItemEffectFactory::createItemEffectTemplate(const QString& effectTypeTag, const QJsonObject& jsonObject)
    {
        Q_ASSERT(isItemEffectTemplateTypeRegistered(effectTypeTag));
        auto constructEffectTemplate = m_effectTemplateConstructors[effectTypeTag];
        std::shared_ptr<ItemEffectTemplate> effectTemplate = constructEffectTemplate(effectTypeTag);
        effectTemplate->read(jsonObject);
        return effectTemplate;
    }

    bool ItemEffectFactory::isItemEffectTypeRegistered(const QString& effectTypeTag)
    {
        return m_effectConstructors.contains(effectTypeTag);
    }

    bool ItemEffectFactory::isItemEffectTemplateTypeRegistered(const QString& effectTypeTag)
    {
        return m_effectTemplateConstructors.contains(effectTypeTag);
    }
}

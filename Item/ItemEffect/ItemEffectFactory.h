#pragma once

#include "ItemEffect.h"

#include <QMap>

namespace ItemSystem
{
    class ItemEffectFactory
    {
    public:
        static std::shared_ptr<ItemEffect> createItemEffect(std::shared_ptr<ItemEffectTemplate> EffectTemplate);
        static std::shared_ptr<ItemEffectTemplate> createItemEffectTemplate(const QString& effectTypeTag, const QJsonObject& jsonObject);

        template<typename EffectType, typename EffectTemplateType>
        static void registerType(const QString& effectTypeTag)
        {
            static_assert(std::is_base_of<ItemEffect, EffectType>::value, "EffectType must inherit from ItemEffect!");
            static_assert(std::is_base_of<ItemEffectTemplate, EffectTemplateType>::value, "EffectTemplateType must inherit from ItemEffectTemplate!");
            m_effectConstructors[effectTypeTag] = &instantiateItemEffect<EffectType>;
            m_effectTemplateConstructors[effectTypeTag] = &instantiateItemEffectTemplate<EffectTemplateType>;
        }

    private:
        static bool isItemEffectTypeRegistered(const QString& effectTypeTag);
        static bool isItemEffectTemplateTypeRegistered(const QString& effectTypeTag);

        template<typename EffectType>
        static std::shared_ptr<ItemEffect> instantiateItemEffect(std::shared_ptr<ItemEffectTemplate> effectTemplate)
        {
            static_assert(std::is_base_of<ItemEffect, EffectType>::value, "EffectType must inherit from ItemEffect!");
            return std::make_shared<EffectType>(effectTemplate);
        }

        template<typename EffectTemplateType>
        static std::shared_ptr<ItemEffectTemplate> instantiateItemEffectTemplate(const QString& typeTag)
        {
            static_assert(std::is_base_of<ItemEffectTemplate, EffectTemplateType>::value, "EffectTemplateType must inherit from ItemEffectTemplate!");
            return std::make_shared<EffectTemplateType>(typeTag);
        }

        static QMap<QString, std::shared_ptr<ItemEffect>(*)(std::shared_ptr<ItemEffectTemplate>)> m_effectConstructors;
        static QMap<QString, std::shared_ptr<ItemEffectTemplate>(*)(const QString&)> m_effectTemplateConstructors;
    };
}

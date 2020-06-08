#include "ItemTimedEffect.h"

#include "ItemEffectFactory.h"

namespace ItemSystem
{
    ItemTimedEffect::ItemTimedEffect(std::shared_ptr<ItemEffectTemplate> itemEffectTemplate) :
        ItemEffect(itemEffectTemplate),
        m_itemTimedEffectTemplate(std::dynamic_pointer_cast<ItemTimedEffectTemplate>(itemEffectTemplate))
    {
        Q_CHECK_PTR(m_itemTimedEffectTemplate);

        for (auto passiveItemEffectTemplate : m_itemTimedEffectTemplate->getItemPassiveEffectTemplates())
        {
            std::shared_ptr<ItemPassiveEffect> itemPassiveEffect = std::dynamic_pointer_cast<ItemPassiveEffect>(ItemEffectFactory::createItemEffect(passiveItemEffectTemplate));
            if(itemPassiveEffect)
                m_itemPassiveEffects.append(itemPassiveEffect);
        }
    }

    ItemTimedEffect::~ItemTimedEffect()
    {
    }

    void ItemTimedEffect::randomize()
    {
        float difference = getMaxDuration() - getMinDuration();
        m_duration = getMinDuration() + m_randomGenerator.generateDouble() * difference;

        for (auto itemPassiveEffect : m_itemPassiveEffects)
            itemPassiveEffect->randomize();
    }

    QList<std::shared_ptr<PassiveEffect>> ItemTimedEffect::createPassiveEffects(std::shared_ptr<EffectTarget> target)
    {
        QList<std::shared_ptr<PassiveEffect>> passiveEffects;
        for (auto itemPassiveEffect : m_itemPassiveEffects)
        {
            auto passiveEffect = std::dynamic_pointer_cast<PassiveEffect>(itemPassiveEffect->createEffect(target));
            if (passiveEffect)
                passiveEffects.append(passiveEffect);
        }
        return passiveEffects;
    }

    float ItemTimedEffect::getMinDuration() const
    {
        return m_itemTimedEffectTemplate->getMinDuration();
    }

    float ItemTimedEffect::getMaxDuration() const
    {
        return m_itemTimedEffectTemplate->getMaxDuration();
    }

    float ItemTimedEffect::getDuration() const
    {
        return m_duration;
    }

    const QList<std::shared_ptr<ItemPassiveEffect>>& ItemTimedEffect::getItemPassiveEffects()
    {
        return m_itemPassiveEffects;
    }
}

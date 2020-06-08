#pragma once

#include "ItemPassiveEffect.h"
#include "ItemTimedEffectTemplate.h"

namespace ItemSystem
{
    /**
    *  @ingroup item_effect_group
    *  @brief Resoponsible for the timing of the ItemEffect
    */
    class ItemTimedEffect : public ItemEffect
    {
    public:
        ItemTimedEffect(std::shared_ptr<ItemEffectTemplate> itemEffectTemplate);
        virtual ~ItemTimedEffect();

        virtual void randomize() override;

        float getMinDuration() const;
        float getMaxDuration() const;
        float getDuration() const;
        const QList<std::shared_ptr<ItemPassiveEffect>>& getItemPassiveEffects();

    protected:
        QList<std::shared_ptr<PassiveEffect>> createPassiveEffects(std::shared_ptr<EffectTarget> target);

        std::shared_ptr<ItemTimedEffectTemplate> m_itemTimedEffectTemplate;
        QList<std::shared_ptr<ItemPassiveEffect>> m_itemPassiveEffects;
        float m_duration;
    };
}

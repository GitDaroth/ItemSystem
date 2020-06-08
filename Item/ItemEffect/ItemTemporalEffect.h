#pragma once

#include "ItemTimedEffect.h"
#include "ItemTemporalEffectTemplate.h"

namespace ItemSystem
{
    class ItemTemporalEffect : public ItemTimedEffect
    {
    public:
        ItemTemporalEffect(std::shared_ptr<ItemEffectTemplate> itemEffectTemplate);
        virtual ~ItemTemporalEffect();

        virtual std::shared_ptr<Effect> createEffect(std::shared_ptr<EffectTarget> target) override;

    protected:
        std::shared_ptr<ItemTemporalEffectTemplate> m_itemTemporalEffectTemplate;
    };
}

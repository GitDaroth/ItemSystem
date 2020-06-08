#pragma once

#include "ItemTimedEffect.h"
#include "ItemOverTimeEffectTemplate.h"

namespace ItemSystem
{
    class ItemOverTimeEffect : public ItemTimedEffect
    {
    public:
        ItemOverTimeEffect(std::shared_ptr<ItemEffectTemplate> itemEffectTemplate);
        virtual ~ItemOverTimeEffect();

        virtual std::shared_ptr<Effect> createEffect(std::shared_ptr<EffectTarget> target) override;

        float getUpdateInterval() const;

    protected:
        std::shared_ptr<ItemOverTimeEffectTemplate> m_itemOverTimeEffectTemplate;
    };
}

#pragma once

#include "ItemEffect.h"
#include "ItemPassiveEffectTemplate.h"
#include "../../Effect/PassiveEffect.h"

namespace ItemSystem
{
    class ItemPassiveEffect : public ItemEffect
    {
    public:
        ItemPassiveEffect(std::shared_ptr<ItemEffectTemplate> itemEffectTemplate);
        ~ItemPassiveEffect();

        void unapply();
        std::shared_ptr<Effect> createEffect(std::shared_ptr<EffectTarget> target) override;

    protected:
        virtual std::shared_ptr<PassiveEffect> createPassiveEffect(std::shared_ptr<EffectTarget> target) = 0;

        std::shared_ptr<ItemPassiveEffectTemplate> m_itemPassiveEffectTemplate;
        std::shared_ptr<PassiveEffect> m_passiveEffect;
    };
}

#pragma once

#include "ItemPassiveEffect.h"
#include "ItemAttributeEffectTemplate.h"

namespace ItemSystem
{
    /**
    *  @ingroup item_effect_group
    *  @brief PassiveItemEffect for Attributes
    */
    class ItemAttributeEffect : public ItemPassiveEffect
    {
    public:
        ItemAttributeEffect(std::shared_ptr<ItemEffectTemplate> itemEffectTemplate);
        virtual ~ItemAttributeEffect();

        virtual void randomize() override;

        QString getAttributeTag() const;
        QString getModifierMethod() const;
        float getMinModifierValue() const;
        float getMaxModifierValue() const;
        float getModifierValue() const;

    protected:
        virtual std::shared_ptr<PassiveEffect> createPassiveEffect(std::shared_ptr<EffectTarget> target) override;

        std::shared_ptr<ItemAttributeEffectTemplate> m_itemAttributeEffectTemplate;
        float m_modifierValue;
    };
}

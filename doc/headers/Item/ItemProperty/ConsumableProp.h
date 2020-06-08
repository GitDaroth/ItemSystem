#pragma once

#include "ItemProperty.h"
#include "../ItemEffect/ItemEffect.h"
#include "ConsumablePropTemplate.h"

namespace ItemSystem
{
    /**
    *  @ingroup item_prop_group
    *  @brief ItemProperty that manages the consume behaviour of the item by applying multiple ItemEffects
    */
    class ConsumableProp : public ItemProperty
    {
    public:
        ConsumableProp(std::shared_ptr<Item> item, std::shared_ptr<ItemPropertyTemplate> propertyTemplate);
        virtual ~ConsumableProp();

        virtual std::shared_ptr<ItemProperty> copy() const override;
        virtual void update(float deltaTime) override;

        /**
        *  @brief Applies ItemEffects on the specified EffectTarget
        */
        void consume(std::shared_ptr<EffectTarget> target);
        void restartCooldown();
        /**
        *  @brief Sets the remaining cooldown time to zero
        */
        void expireCooldown();

        bool isOnCooldown() const;
        bool isUnlimited() const;
        float getRemainingCooldownTime() const;
        float getCooldown() const;
        QString getEffectTargetMethod() const;
        const QList<std::shared_ptr<ItemEffect>>& getItemEffects();

        void setRemainingCooldownTime(float remainingCooldownTime);

    protected:
        std::shared_ptr<ConsumablePropTemplate> m_consumablePropTemplate;
        QList<std::shared_ptr<ItemEffect>> m_itemEffects;
        float m_remainingCooldownTime;
    };
}

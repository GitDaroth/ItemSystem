#pragma once

#include "ItemProperty.h"
#include "../ItemEffect/ItemPassiveEffect.h"
#include "EquipablePropTemplate.h"

namespace ItemSystem
{
    /**
    *  @ingroup item_prop_group
    *  @brief ItemProperty that manages the equipment behaviour of the item by un/applying multiple ItemPassiveEffects
    */
    class EquipableProp : public ItemProperty
    {
    public:
        EquipableProp(std::shared_ptr<Item> item, std::shared_ptr<ItemPropertyTemplate> propertyTemplate);
        virtual ~EquipableProp();

        virtual std::shared_ptr<ItemProperty> copy() const override;
        virtual void update(float deltaTime) override;

        /**
        *  @brief Applies ItemPassiveEffects to the EffectTarget
        */
        void equip(std::shared_ptr<EffectTarget> target);
        /**
        *  @brief Unapplies ItemPassiveEffects from the last EffectTarget
        */
        void unequip();

        const QList<std::shared_ptr<ItemPassiveEffect>>& getItemPassiveEffects();

    protected:
        std::shared_ptr<EquipablePropTemplate> m_equipablePropTemplate;
        QList<std::shared_ptr<ItemPassiveEffect>> m_itemPassiveEffects;
    };
}

#pragma once

#include "ItemProperty.h"
#include "../ItemEffect/ItemPassiveEffect.h"
#include "EquipablePropTemplate.h"

namespace ItemSystem
{
    class EquipableProp : public ItemProperty
    {
    public:
        EquipableProp(std::shared_ptr<Item> item, std::shared_ptr<ItemPropertyTemplate> propertyTemplate);
        virtual ~EquipableProp();

        virtual std::shared_ptr<ItemProperty> copy() const override;
        virtual void update(float deltaTime) override;

        void equip(std::shared_ptr<EffectTarget> target);
        void unequip();

        const QList<std::shared_ptr<ItemPassiveEffect>>& getItemPassiveEffects();

    protected:
        std::shared_ptr<EquipablePropTemplate> m_equipablePropTemplate;
        QList<std::shared_ptr<ItemPassiveEffect>> m_itemPassiveEffects;
    };
}

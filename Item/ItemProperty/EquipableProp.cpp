#include "EquipableProp.h"

#include "../ItemEffect/ItemEffectFactory.h"
#include "ItemPropertyFactory.h"

namespace ItemSystem
{
    EquipableProp::EquipableProp(std::shared_ptr<Item> item, std::shared_ptr<ItemPropertyTemplate> propertyTemplate) :
        ItemProperty(item, propertyTemplate),
        m_equipablePropTemplate(std::dynamic_pointer_cast<EquipablePropTemplate>(propertyTemplate))
    {
        Q_CHECK_PTR(m_equipablePropTemplate);

        for(auto itemPassiveEffectTemplate : m_equipablePropTemplate->getItemPassiveEffectTemplates())
        {
            std::shared_ptr<ItemPassiveEffect> itemPassiveEffect = std::dynamic_pointer_cast<ItemPassiveEffect>(ItemEffectFactory::createItemEffect(itemPassiveEffectTemplate));
            if(itemPassiveEffect)
                m_itemPassiveEffects.append(itemPassiveEffect);
        }
    }

    EquipableProp::~EquipableProp()
    {
    }

    std::shared_ptr<ItemProperty> EquipableProp::copy() const
    {
        std::shared_ptr<ItemProperty> copiedProperty = ItemPropertyFactory::createItemProperty(m_item, m_propertyTemplate);
        std::shared_ptr<EquipableProp> copiedEquipableProp = std::dynamic_pointer_cast<EquipableProp>(copiedProperty);
        return copiedEquipableProp;
    }

    void EquipableProp::update(float deltaTime)
    {
    }

    void EquipableProp::equip(std::shared_ptr<EffectTarget> target)
    {
        for (auto itemPassiveEffect : m_itemPassiveEffects)
            itemPassiveEffect->apply(target);
    }

    void EquipableProp::unequip()
    {
        for (auto itemPassiveEffect : m_itemPassiveEffects)
            itemPassiveEffect->unapply();
    }

    const QList<std::shared_ptr<ItemPassiveEffect>>& EquipableProp::getItemPassiveEffects()
    {
        return m_itemPassiveEffects;
    }
}

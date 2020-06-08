#include "ConsumableProp.h"

#include "../ItemEffect/ItemEffectFactory.h"
#include "ItemPropertyFactory.h"
#include "StackableProp.h"

namespace ItemSystem
{
    ConsumableProp::ConsumableProp(std::shared_ptr<Item> item, std::shared_ptr<ItemPropertyTemplate> propertyTemplate) :
        ItemProperty(item, propertyTemplate),
        m_consumablePropTemplate(std::dynamic_pointer_cast<ConsumablePropTemplate>(propertyTemplate)),
        m_remainingCooldownTime(0.f)
    {
        Q_CHECK_PTR(m_consumablePropTemplate);

        for(auto itemEffectTemplate : m_consumablePropTemplate->getItemEffectTemplates())
            m_itemEffects.append(ItemEffectFactory::createItemEffect(itemEffectTemplate));
    }

    ConsumableProp::~ConsumableProp()
    {
    }

    std::shared_ptr<ItemProperty> ConsumableProp::copy() const
    {
        std::shared_ptr<ItemProperty> copiedProperty = ItemPropertyFactory::createItemProperty(m_item, m_propertyTemplate);
        std::shared_ptr<ConsumableProp> copiedConsumableProp = std::dynamic_pointer_cast<ConsumableProp>(copiedProperty);
        return copiedConsumableProp;
    }

    void ConsumableProp::update(float deltaTime)
    {
        if (isOnCooldown())
        {
            m_remainingCooldownTime -= deltaTime;
            if (m_remainingCooldownTime <= 0.f)
                m_remainingCooldownTime = 0.f;
        }
    }

    void ConsumableProp::consume(std::shared_ptr<EffectTarget> target)
    {
        if (!isOnCooldown())
        {
            if(auto stackableProp = m_item->getProperty<StackableProp>())
                stackableProp->removeStacks(1);

            for (auto itemEffect : m_itemEffects)
                itemEffect->apply(target);
            restartCooldown();
        }
    }

    void ConsumableProp::restartCooldown()
    {
        m_remainingCooldownTime = getCooldown();
    }

    void ConsumableProp::expireCooldown()
    {
        m_remainingCooldownTime = 0.f;
    }

    bool ConsumableProp::isOnCooldown() const
    {
        return m_remainingCooldownTime > 0.f;
    }

    bool ConsumableProp::isUnlimited() const
    {
        return m_consumablePropTemplate->isUnlimited();
    }

    float ConsumableProp::getRemainingCooldownTime() const
    {
        return m_remainingCooldownTime;
    }

    float ConsumableProp::getCooldown() const
    {
        return m_consumablePropTemplate->getCooldown();
    }

    QString ConsumableProp::getEffectTargetMethod() const
    {
        return m_consumablePropTemplate->getEffectTargetMethod();
    }

    const QList<std::shared_ptr<ItemEffect>>& ConsumableProp::getItemEffects()
    {
        return m_itemEffects;
    }

    void ConsumableProp::setRemainingCooldownTime(float remainingCooldownTime)
    {
        m_remainingCooldownTime = remainingCooldownTime;
    }
}

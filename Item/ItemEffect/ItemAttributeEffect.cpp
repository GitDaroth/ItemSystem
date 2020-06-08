#include "ItemAttributeEffect.h"

#include "../../Effect/AttributeEffect.h"

namespace ItemSystem
{
    ItemAttributeEffect::ItemAttributeEffect(std::shared_ptr<ItemEffectTemplate> itemEffectTemplate) :
        ItemPassiveEffect(itemEffectTemplate),
        m_itemAttributeEffectTemplate(std::dynamic_pointer_cast<ItemAttributeEffectTemplate>(itemEffectTemplate))
    {
        Q_CHECK_PTR(m_itemAttributeEffectTemplate);
    }

    ItemAttributeEffect::~ItemAttributeEffect()
    {
    }

    std::shared_ptr<PassiveEffect> ItemAttributeEffect::createPassiveEffect(std::shared_ptr<EffectTarget> target)
    {
        return std::make_shared<AttributeEffect>(target, getAttributeTag(), m_modifierValue, getModifierMethod());
    }

    void ItemAttributeEffect::randomize()
    {
        float difference = getMaxModifierValue() - getMinModifierValue();
        m_modifierValue = getMinModifierValue() + m_randomGenerator.generateDouble() * difference;
    }

    QString ItemAttributeEffect::getAttributeTag() const
    {
        return m_itemAttributeEffectTemplate->getAttributeTag();
    }

    QString ItemAttributeEffect::getModifierMethod() const
    {
        return m_itemAttributeEffectTemplate->getModifierMethod();
    }

    float ItemAttributeEffect::getMinModifierValue() const
    {
        return m_itemAttributeEffectTemplate->getMinModifierValue();
    }

    float ItemAttributeEffect::getMaxModifierValue() const
    {
        return m_itemAttributeEffectTemplate->getMaxModifierValue();
    }

    float ItemAttributeEffect::getModifierValue() const
    {
        return m_modifierValue;
    }
}

#include "AttributeEffect.h"

#include "../Character/Character.h"
#include "../Attribute/AttributeSystem.h"
#include "../Attribute/ResourceAttribute.h"

namespace ItemSystem
{
    AttributeEffect::AttributeEffect(std::shared_ptr<EffectTarget> target, const QString& attributeTag, float modifierValue, const QString& modifierMethod) :
        PassiveEffect(target),
        m_attribute(nullptr),
        m_attributeTag(attributeTag),
        m_modifierMethod(modifierMethod),
        m_modifierValue(modifierValue),
        m_modifierImpactValue(0.f),
        m_appliedValue(0.f)
    {
        if(auto character = std::dynamic_pointer_cast<Character>(m_target))
            if(auto attributeSystem = character->getComponent<AttributeSystem>())
                m_attribute = attributeSystem->getAttribute(m_attributeTag);
    }

    AttributeEffect::~AttributeEffect()
    {
    }

    void AttributeEffect::update(float deltaTime)
    {
    }

    void AttributeEffect::onApplyPartially(float ratio)
    {
        if (!m_attribute)
            return;


        if (auto resourceAttribute = std::dynamic_pointer_cast<ResourceAttribute>(m_attribute))
        {
            if (!m_hasBeenApplied)
                m_modifierImpactValue = resourceAttribute->getModifierImpact(AttributeModifier(m_modifierValue, m_modifierMethod));

            float additionalAppliedValue = m_modifierImpactValue * ratio;
            m_appliedValue += additionalAppliedValue;
            m_attribute->applyModifier(AttributeModifier(additionalAppliedValue, "additive"));
        }
        else
        {
            if (m_modifierMethod == "total_factor")
            {
                if (!m_hasBeenApplied)
                    m_appliedValue = 1.f;
                else
                    m_attribute->applyModifier(AttributeModifier(1.f / m_appliedValue, m_modifierMethod));

                m_appliedValue += (m_modifierValue - 1.f) * ratio;
                m_attribute->applyModifier(AttributeModifier(m_appliedValue, m_modifierMethod));
            }
            else
            {
                float additionalAppliedValue = m_modifierValue * ratio;
                m_appliedValue += additionalAppliedValue;
                m_attribute->applyModifier(AttributeModifier(additionalAppliedValue, m_modifierMethod));
            }
        }
    }

    void AttributeEffect::onUnapply()
    {
        if (!m_attribute)
            return;

        if (std::dynamic_pointer_cast<ResourceAttribute>(m_attribute))
            m_attribute->applyModifier(AttributeModifier(-m_appliedValue, "additive"));
        else
        {
            if(m_modifierMethod == "total_factor")
                m_attribute->applyModifier(AttributeModifier(1.f / m_appliedValue, m_modifierMethod));
            else
                m_attribute->applyModifier(AttributeModifier(-m_appliedValue, m_modifierMethod));
        }

        m_appliedValue = 0.f;
    }
}

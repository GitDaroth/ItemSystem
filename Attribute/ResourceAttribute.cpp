#include "ResourceAttribute.h"

#include <QtMath>

namespace ItemSystem
{
    ResourceAttribute::ResourceAttribute(const QString& tag, const QString& name, std::shared_ptr<TraitAttribute> maxAttribute) :
        Attribute(tag, name),
        m_maxAttribute(maxAttribute),
        m_regenerationAttribute(nullptr)
    {
    }

    ResourceAttribute::~ResourceAttribute()
    {
    }

    void ResourceAttribute::update(float deltaTime)
    {
        if(m_regenerationAttribute)
        {
            float regenerationValue = m_regenerationAttribute->getFinalValue() * deltaTime;
            applyModifier(AttributeModifier(regenerationValue, "additive"));
        }
    }

    void ResourceAttribute::applyModifier(const AttributeModifier& modifier)
    {
        m_baseValue += getModifierImpact(modifier);
    }

    float ResourceAttribute::getFinalValue() const
    {
        return m_baseValue;
    }

    float ResourceAttribute::getModifierImpact(const AttributeModifier& modifier) const
    {
        float expectedValue = m_baseValue;
        QString method = modifier.method;
        if (method == "additive")
            expectedValue += modifier.value;
        else if (method == "multiplicative")
            expectedValue *= 1.f + modifier.value;
        else if (method == "total_factor")
            expectedValue *= modifier.value;

        expectedValue = clampValue(expectedValue);
        return expectedValue - m_baseValue;
    }

    float ResourceAttribute::clampValue(float value) const
    {
        return qMin(qMax(value, m_minValue), m_maxAttribute->getFinalValue());
    }

    std::shared_ptr<TraitAttribute> ResourceAttribute::getRegenerationAttribute()
    {
        return m_regenerationAttribute;
    }

    std::shared_ptr<TraitAttribute> ResourceAttribute::getMaxAttribute()
    {
        return m_maxAttribute;
    }

    void ResourceAttribute::setRegenerationAttribute(std::shared_ptr<TraitAttribute> regenerationAttribute)
    {
        m_regenerationAttribute = regenerationAttribute;
    }

    void ResourceAttribute::setMaxAttribute(std::shared_ptr<TraitAttribute> maxAttribute)
    {
        m_maxAttribute = maxAttribute;
    }
}

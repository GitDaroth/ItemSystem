#include "TraitAttribute.h"

#include <QtMath>
#include <QMapIterator>

namespace ItemSystem
{
    TraitAttribute::TraitAttribute(const QString& tag, const QString& name) :
        Attribute(tag, name),
        m_maxValue(999999.f),
        m_additiveValue(0.f),
        m_multiplicativeValue(1.f),
        m_totalFactorValue(1.f)
    {
    }

    TraitAttribute::~TraitAttribute()
    {
    }

    void TraitAttribute::update(float deltaTime)
    {
    }

    void TraitAttribute::applyModifier(const AttributeModifier& modifier)
    {
        QString method = modifier.method;
        if (method == "additive")
            m_additiveValue += modifier.value;
        else if (method == "multiplicative")
            m_multiplicativeValue += modifier.value;
        else if (method == "total_factor")
            m_totalFactorValue *= modifier.value;
    }

    float TraitAttribute::getFinalValue() const
    {
        float influenceValue = 0.f;
        QMapIterator<std::shared_ptr<TraitAttribute>, float> iter(m_influencingAttributes);
        while(iter.hasNext())
        {
            iter.next();
            influenceValue += iter.value() * iter.key()->getFinalValue();
        }

        return clampValue((m_baseValue + influenceValue + m_additiveValue) * m_multiplicativeValue * m_totalFactorValue);
    }

    void TraitAttribute::addInfluencingAttribute(std::shared_ptr<TraitAttribute> attribute, float influence)
    {
        m_influencingAttributes.insert(attribute, influence);
    }

    void TraitAttribute::clearInfluencingAttributes()
    {
        m_influencingAttributes.clear();
    }

    float TraitAttribute::clampValue(float value) const
    {
        return qMin(qMax(value, m_minValue), m_maxValue);
    }

    float TraitAttribute::getMaxValue() const
    {
        return m_maxValue;
    }

    void TraitAttribute::setMaxValue(float maxValue)
    {
        m_maxValue = maxValue;
    }
}

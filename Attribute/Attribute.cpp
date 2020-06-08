#include "Attribute.h"

namespace ItemSystem
{
    Attribute::Attribute(const QString& tag, const QString& name) :
        m_tag(tag),
        m_name(name),
        m_baseValue(0.f),
        m_minValue(0.f)
    {
    }

    Attribute::~Attribute()
    {
    }

    QString Attribute::getTag() const
    {
        return m_tag;
    }

    QString Attribute::getName() const
    {
        return m_name;
    }

    float Attribute::getMinValue() const
    {
        return m_minValue;
    }

    float Attribute::getBaseValue() const
    {
        return m_baseValue;
    }

    void Attribute::setMinValue(float minValue)
    {
        m_minValue = minValue;
    }

    void Attribute::setBaseValue(float baseValue)
    {
        m_baseValue = baseValue;
    }
}

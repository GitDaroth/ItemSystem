#pragma once

#include "Attribute.h"

#include <QMap>
#include <memory>

namespace ItemSystem
{
    class TraitAttribute : public Attribute
    {
    public:
        TraitAttribute(const QString& tag, const QString& name);
        virtual ~TraitAttribute();

        virtual void update(float deltaTime) override;
        virtual void applyModifier(const AttributeModifier& modifier) override;
        virtual float getFinalValue() const override;

        void addInfluencingAttribute(std::shared_ptr<TraitAttribute> attribute, float influence);
        void clearInfluencingAttributes();

        float getMaxValue() const;
        void setMaxValue(float maxValue);

    protected:
        virtual float clampValue(float value) const override;

        float m_maxValue;
        float m_additiveValue;
        float m_multiplicativeValue;
        float m_totalFactorValue;
        QMap<std::shared_ptr<TraitAttribute>, float> m_influencingAttributes;
    };
}

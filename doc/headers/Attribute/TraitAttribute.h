#pragma once

#include "Attribute.h"

#include <QMap>
#include <memory>

namespace ItemSystem
{
    /**
    *  @ingroup attribute
    *  @brief This Attribute applies modifiers not directly to the base value (ex. damage, max. health)
    */
    class TraitAttribute : public Attribute
    {
    public:
        TraitAttribute(const QString& tag, const QString& name);
        virtual ~TraitAttribute();

        virtual void update(float deltaTime) override;
        virtual void applyModifier(const AttributeModifier& modifier) override;
        virtual float getFinalValue() const override;

        /**
        *  @brief Adds an attribute that influences the attribute by a percentage of the final value of the added attribute
        */
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

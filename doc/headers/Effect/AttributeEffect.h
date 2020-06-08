#pragma once

#include "PassiveEffect.h"
#include "../Attribute/Attribute.h"

namespace ItemSystem
{
    /**
    *  @ingroup effect
    *  @brief Responsible for applying and unapplying the Effect to/from the given Attribute
    */
    class AttributeEffect : public PassiveEffect
    {
    public:
        explicit AttributeEffect(std::shared_ptr<EffectTarget> target, const QString& attributeTag, float modifierValue, const QString& modifierMethod);
        virtual ~AttributeEffect();

        virtual void update(float deltaTime) override;

    protected:
        virtual void onApplyPartially(float ratio)  override;
        virtual void onUnapply() override;

        std::shared_ptr<Attribute> m_attribute;
        QString m_attributeTag;
        QString m_modifierMethod;
        float m_modifierValue;
        float m_modifierImpactValue;
        float m_appliedValue;
    };
}

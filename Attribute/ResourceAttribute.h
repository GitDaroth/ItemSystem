#pragma once

#include "TraitAttribute.h"

namespace ItemSystem
{
class ResourceAttribute : public Attribute
{
    public:
        explicit ResourceAttribute(const QString& tag, const QString& name, std::shared_ptr<TraitAttribute> maxAttribute);
        virtual ~ResourceAttribute();

        virtual void update(float deltaTime) override;
        virtual void applyModifier(const AttributeModifier& modifier) override;
        virtual float getFinalValue() const override;
        virtual float getModifierImpact(const AttributeModifier& modifier) const;

        std::shared_ptr<TraitAttribute> getRegenerationAttribute();
        std::shared_ptr<TraitAttribute> getMaxAttribute();

        void setRegenerationAttribute(std::shared_ptr<TraitAttribute> regenerationAttribute);
        void setMaxAttribute(std::shared_ptr<TraitAttribute> maxAttribute);

    protected:
        virtual float clampValue(float value) const override;

        std::shared_ptr<TraitAttribute> m_maxAttribute;
        std::shared_ptr<TraitAttribute> m_regenerationAttribute;
    };
}

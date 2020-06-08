#pragma once

#include <QString>

namespace ItemSystem
{
    struct AttributeModifier
    {
        AttributeModifier(float value, const QString& method)
        {
            this->value = value;
            this->method = method;
        }

        float value;
        QString method;
    };

    class Attribute
    {
    public:
        Attribute(const QString& tag, const QString& name);
        virtual ~Attribute();

        virtual void update(float deltaTime) = 0;
        virtual void applyModifier(const AttributeModifier& modifier) = 0;
        virtual float getFinalValue() const = 0;

        QString getTag() const;
        QString getName() const;
        float getMinValue() const;
        float getBaseValue() const;

        void setMinValue(float minValue);
        void setBaseValue(float baseValue);

    protected:
        virtual float clampValue(float value) const = 0;

        QString m_tag;
        QString m_name;
        float m_baseValue;
        float m_minValue;
    };
}

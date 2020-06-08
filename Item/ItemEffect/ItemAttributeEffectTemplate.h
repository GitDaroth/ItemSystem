#pragma once

#include "ItemPassiveEffectTemplate.h"

namespace ItemSystem
{
    class ItemAttributeEffectTemplate : public ItemPassiveEffectTemplate
    {
    public:
        ItemAttributeEffectTemplate(const QString& typeTag);
        virtual ~ItemAttributeEffectTemplate();

        QString getAttributeTag() const;
        QString getModifierMethod() const;
        float getMinModifierValue() const;
        float getMaxModifierValue() const;

    protected:
        virtual void read(const QJsonObject& jsonObject) override;

        QString m_attributeTag;
        QString m_modifierMethod;
        float m_minModifierValue;
        float m_maxModifierValue;

    private:
        void readAttributeTag(const QJsonObject& jsonObject);
        void readModifierMethod(const QJsonObject& jsonObject);
        void readModifierValue(const QJsonObject& jsonObject);
    };
}

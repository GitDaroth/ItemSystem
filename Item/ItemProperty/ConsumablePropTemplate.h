#pragma once

#include "ItemPropertyTemplate.h"
#include "../ItemEffect/ItemEffectTemplate.h"

#include <memory>
#include <QList>

namespace ItemSystem
{
    class ConsumablePropTemplate : public ItemPropertyTemplate
    {
    public:
        ConsumablePropTemplate(const QString& typeTag);
        virtual ~ConsumablePropTemplate();

        virtual void read(const QJsonObject& jsonObject) override;

        float getCooldown() const;
        bool isUnlimited() const;
        QString getEffectTargetMethod() const;
        const QList<std::shared_ptr<ItemEffectTemplate>>& getItemEffectTemplates();

    protected:
        float m_cooldown;
        bool m_isUnlimited;
        QString m_effectTargetMethod;
        QList<std::shared_ptr<ItemEffectTemplate>> m_itemEffectTemplates;

    private:
        void readCooldown(const QJsonObject& jsonObject);
        void readIsUnlimited(const QJsonObject& jsonObject);
        void readEffectTargetMethod(const QJsonObject& jsonObject);
        void readItemEffects(const QJsonObject& jsonObject);
        void readItemEffect(const QJsonObject& effectWrapperJsonObject);
    };
}

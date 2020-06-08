#pragma once

#include "ItemPropertyTemplate.h"
#include "../ItemEffect/ItemPassiveEffectTemplate.h"

#include <memory>
#include <QList>

namespace ItemSystem
{
    class EquipablePropTemplate : public ItemPropertyTemplate
    {
    public:
        EquipablePropTemplate(const QString& typeTag);
        virtual ~EquipablePropTemplate();

        virtual void read(const QJsonObject& jsonObject) override;

        const QList<std::shared_ptr<ItemPassiveEffectTemplate>>& getItemPassiveEffectTemplates();

    protected:
        QList<std::shared_ptr<ItemPassiveEffectTemplate>> m_itemPassiveEffectTemplates;

    private:
        void readItemPassiveEffects(const QJsonObject& jsonObject);
        void readItemPassiveEffect(const QJsonObject& passiveEffectWrapperJsonObject);
    };
}

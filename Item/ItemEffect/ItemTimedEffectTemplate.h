#pragma once

#include "ItemPassiveEffectTemplate.h"

#include <memory>
#include <QList>

namespace ItemSystem
{
    class ItemTimedEffectTemplate : public ItemEffectTemplate
    {
    public:
        ItemTimedEffectTemplate(const QString& typeTag);
        virtual ~ItemTimedEffectTemplate();

        float getMinDuration() const;
        float getMaxDuration() const;
        const QList<std::shared_ptr<ItemPassiveEffectTemplate>>& getItemPassiveEffectTemplates();

    protected:
        virtual void read(const QJsonObject& jsonObject) override;
        virtual void onRead(const QJsonObject& jsonObject) = 0;

        float m_minDuration;
        float m_maxDuration;
        QList<std::shared_ptr<ItemPassiveEffectTemplate>> m_itemPassiveEffectTemplates;

    private:
        void readDuration(const QJsonObject& jsonObject);
        void readPassiveEffects(const QJsonObject& jsonObject);
        void readPassiveEffect(const QJsonObject& passiveEffectWrapperJsonObject);
    };
}

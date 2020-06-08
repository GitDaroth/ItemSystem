#pragma once

#include "ItemTimedEffectTemplate.h"

namespace ItemSystem
{
    class ItemTemporalEffectTemplate : public ItemTimedEffectTemplate
    {
    public:
        ItemTemporalEffectTemplate(const QString& typeTag);
        virtual ~ItemTemporalEffectTemplate();

    protected:
        virtual void onRead(const QJsonObject& jsonObject) override;
    };
}

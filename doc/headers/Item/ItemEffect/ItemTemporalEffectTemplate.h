#pragma once

#include "ItemTimedEffectTemplate.h"

namespace ItemSystem
{
	/**
	*  @ingroup item_effect_group
	*/
    class ItemTemporalEffectTemplate : public ItemTimedEffectTemplate
    {
    public:
        ItemTemporalEffectTemplate(const QString& typeTag);
        virtual ~ItemTemporalEffectTemplate();

    protected:
        virtual void onRead(const QJsonObject& jsonObject) override;
    };
}

#pragma once

#include "ItemTimedEffectTemplate.h"

namespace ItemSystem
{
	/**
	*  @ingroup item_effect_group
	*/
    class ItemOverTimeEffectTemplate : public ItemTimedEffectTemplate
    {
    public:
        ItemOverTimeEffectTemplate(const QString& typeTag);
        virtual ~ItemOverTimeEffectTemplate();

        float getUpdateInterval() const;

    protected:
        virtual void onRead(const QJsonObject& jsonObject) override;

        float m_updateInterval;

    private:
        void readUpdateInterval(const QJsonObject& jsonObject);
    };
}

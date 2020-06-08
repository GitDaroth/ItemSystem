#include "ItemTemporalEffectTemplate.h"

namespace ItemSystem
{
    ItemTemporalEffectTemplate::ItemTemporalEffectTemplate(const QString& typeTag) :
        ItemTimedEffectTemplate(typeTag)
    {
    }

    ItemTemporalEffectTemplate::~ItemTemporalEffectTemplate()
    {
    }

    void ItemTemporalEffectTemplate::onRead(const QJsonObject& jsonObject)
    {
    }
}


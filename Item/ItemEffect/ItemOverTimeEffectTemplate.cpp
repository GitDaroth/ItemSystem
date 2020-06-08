#include "ItemOverTimeEffectTemplate.h"

namespace ItemSystem
{
    ItemOverTimeEffectTemplate::ItemOverTimeEffectTemplate(const QString& typeTag) :
        ItemTimedEffectTemplate(typeTag)
    {
    }

    ItemOverTimeEffectTemplate::~ItemOverTimeEffectTemplate()
    {
    }

    void ItemOverTimeEffectTemplate::onRead(const QJsonObject& jsonObject)
    {
        readUpdateInterval(jsonObject);
    }

    void ItemOverTimeEffectTemplate::readUpdateInterval(const QJsonObject& jsonObject)
    {
        QJsonValue updateIntervalJsonValue = jsonObject.value("update_interval");
        Q_ASSERT(updateIntervalJsonValue.isDouble());
        m_updateInterval = qMax((float)updateIntervalJsonValue.toDouble(), 0.f);
    }

    float ItemOverTimeEffectTemplate::getUpdateInterval() const
    {
        return m_updateInterval;
    }
}

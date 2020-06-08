#include "OverTimeEffect.h"

namespace ItemSystem
{
    OverTimeEffect::OverTimeEffect(std::shared_ptr<EffectTarget> target, float updateInterval, float duration, const QList<std::shared_ptr<PassiveEffect>>& passiveEffects) :
        TimedEffect(target, duration, passiveEffects),
        m_updateInterval(updateInterval),
        m_targetIntervalTime(m_updateInterval),
        m_remainingIntervalTime(m_updateInterval),
        m_appliedRatio(0.f)
    {
    }

    OverTimeEffect::~OverTimeEffect()
    {
    }

    void OverTimeEffect::onUpdate(float deltaTime)
    {
        m_remainingIntervalTime -= deltaTime;
        if (m_remainingIntervalTime <= 0.f)
        {
            float appliedRatioOffset = (m_targetIntervalTime - m_remainingIntervalTime) / m_duration;
            m_appliedRatio += appliedRatioOffset;
            for (auto passiveEffect : m_passiveEffects)
            {
                passiveEffect->applyPartially(appliedRatioOffset);
            }
            m_targetIntervalTime = m_updateInterval + m_remainingIntervalTime;
            m_remainingIntervalTime = m_targetIntervalTime;
        }
    }

    void OverTimeEffect::onStart()
    {
        m_targetIntervalTime = m_updateInterval;
        m_remainingIntervalTime = m_updateInterval;
        m_appliedRatio = 0.f;
    }

    void OverTimeEffect::onStop()
    {
        for (auto passiveEffect : m_passiveEffects)
        {
            float targetRatio = 1.f - (m_remainingTime / m_duration);
            float appliedRatioOffset = targetRatio - m_appliedRatio;
            passiveEffect->applyPartially(appliedRatioOffset);
        }
    }
}

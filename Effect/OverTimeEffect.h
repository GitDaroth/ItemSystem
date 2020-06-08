#pragma once

#include "TimedEffect.h"

namespace ItemSystem
{
    class OverTimeEffect : public TimedEffect
    {
    public:
        explicit OverTimeEffect(std::shared_ptr<EffectTarget> target, float updateInterval, float duration, const QList<std::shared_ptr<PassiveEffect>>& passiveEffects);
        virtual ~OverTimeEffect();

    protected:
        virtual void onUpdate(float deltaTime) override;
        virtual void onStart() override;
        virtual void onStop() override;

        float m_updateInterval;
        float m_targetIntervalTime;
        float m_remainingIntervalTime;
        float m_appliedRatio;
    };
}

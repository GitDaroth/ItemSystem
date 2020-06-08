#pragma once

#include "TimedEffect.h"

namespace ItemSystem
{
    class TemporalEffect : public TimedEffect
    {
    public:
        explicit TemporalEffect(std::shared_ptr<EffectTarget> target, float duration, const QList<std::shared_ptr<PassiveEffect>>& passiveEffects);
        virtual ~TemporalEffect();

    protected:
        virtual void onUpdate(float deltaTime) override;
        virtual void onStart() override;
        virtual void onStop() override;
    };
}

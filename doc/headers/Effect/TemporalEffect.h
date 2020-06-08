#pragma once

#include "TimedEffect.h"

namespace ItemSystem
{
    /**
    *  @ingroup effect
    *  @brief Responsible for applying the Effect for a timed duration. Unapplies the Effect when the duration is reached
    */
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

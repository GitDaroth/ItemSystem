#include "TemporalEffect.h"

namespace ItemSystem
{
    TemporalEffect::TemporalEffect(std::shared_ptr<EffectTarget> target, float duration, const QList<std::shared_ptr<PassiveEffect>>& passiveEffects) :
        TimedEffect(target, duration, passiveEffects)
    {
    }

    TemporalEffect::~TemporalEffect()
    {
    }

    void TemporalEffect::onUpdate(float deltaTime)
    {
    }

    void TemporalEffect::onStart()
    {
        for (auto passiveEffect : m_passiveEffects)
        {
            passiveEffect->apply();
        }
    }

    void TemporalEffect::onStop()
    {
        for (auto passiveEffect : m_passiveEffects)
        {
            passiveEffect->unapply();
        }
    }
}

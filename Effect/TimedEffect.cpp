#include "TimedEffect.h"

#include "EffectSystem.h"

#include <QDebug>

namespace ItemSystem
{
    TimedEffect::TimedEffect(std::shared_ptr<EffectTarget> target, float duration, const QList<std::shared_ptr<PassiveEffect>>& passiveEffects) :
        Effect(target),
        m_duration(duration),
        m_remainingTime(duration),
        m_isActive(false),
        m_passiveEffects(passiveEffects)
    {
    }

    TimedEffect::~TimedEffect()
    {
    }

    void TimedEffect::update(float deltaTime)
    {
        if (m_isActive)
        {
            onUpdate(deltaTime);

            m_remainingTime -= deltaTime;
            if (m_remainingTime <= 0.f)
            {
                m_remainingTime = 0.f;
                stop();
            }
        }
    }

    void TimedEffect::onApply()
    {
        onStart();
        m_isActive = true;
    }

    void TimedEffect::stop()
    {
        EffectSystem::getInstance()->removeEffect(shared_from_this());

        onStop();
        m_remainingTime = m_duration;
        m_isActive = false;
    }
}

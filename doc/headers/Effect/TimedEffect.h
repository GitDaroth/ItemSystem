#pragma once

#include "PassiveEffect.h"

#include <QList>

namespace ItemSystem
{
    /**
    *  @ingroup effect
    *  @brief Responsible for timing the Effect
    */
    class TimedEffect : public Effect
    {
    public:
        explicit TimedEffect(std::shared_ptr<EffectTarget> target, float duration, const QList<std::shared_ptr<PassiveEffect>>& passiveEffects);
        virtual ~TimedEffect();

        virtual void update(float deltaTime) override;
        void stop();

    protected:
        void onApply() override;
        virtual void onUpdate(float deltaTime) = 0;
        virtual void onStart() = 0;
        virtual void onStop() = 0;

        float m_duration;
        float m_remainingTime;
        bool m_isActive;
        QList<std::shared_ptr<PassiveEffect>> m_passiveEffects;
    };
}

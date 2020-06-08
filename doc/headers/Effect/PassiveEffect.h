#pragma once

#include "Effect.h"

namespace ItemSystem
{
    /**
    *  @ingroup effect
    *  @brief Responsible for partially applying and unapplying the PassiveEffect
    */
    class PassiveEffect : public Effect
    {
    public:
        explicit PassiveEffect(std::shared_ptr<EffectTarget> target);
        virtual ~PassiveEffect();

        void applyPartially(float ratio);
        void unapply();

    protected:
        void onApply() override;
        virtual void onApplyPartially(float ratio) = 0;
        virtual void onUnapply() = 0;

        bool m_hasBeenApplied;
    };
}

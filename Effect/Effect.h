#pragma once

#include "EffectTarget.h"

#include <memory>

namespace ItemSystem
{
    class Effect : public std::enable_shared_from_this<Effect>
    {
    public:
        explicit Effect(std::shared_ptr<EffectTarget> target);
        virtual ~Effect();

        virtual void update(float deltaTime) = 0;
        void apply();

    protected:
        virtual void onApply() = 0;

        std::shared_ptr<EffectTarget> m_target;
    };
}

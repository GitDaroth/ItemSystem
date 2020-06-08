#pragma once

namespace ItemSystem
{
    /**
    *  @ingroup effect
    *  @brief Interface for an EffectTarget
    */
    class EffectTarget
    {
    public:
        virtual void update(float deltaTime) = 0;
    };
}

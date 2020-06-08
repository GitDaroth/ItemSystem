#pragma once

namespace ItemSystem
{
    class EffectTarget
    {
    public:
        virtual void update(float deltaTime) = 0;
    };
}

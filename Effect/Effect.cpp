#include "Effect.h"

#include "EffectSystem.h"

namespace ItemSystem
{
    Effect::Effect(std::shared_ptr<EffectTarget> target) :
        m_target(target)
    {
    }

    Effect::~Effect()
    {
    }

    void Effect::apply()
    {
        EffectSystem::getInstance()->addEffect(shared_from_this());
        onApply();
    }
}

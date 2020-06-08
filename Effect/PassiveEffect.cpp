#include "PassiveEffect.h"

#include "EffectSystem.h"

namespace ItemSystem
{
    PassiveEffect::PassiveEffect(std::shared_ptr<EffectTarget> target) :
        Effect(target),
        m_hasBeenApplied(false)
    {
    }

    PassiveEffect::~PassiveEffect()
    {
    }

    void PassiveEffect::onApply()
    {
        if (m_hasBeenApplied)
            EffectSystem::getInstance()->removeEffect(shared_from_this());

        onApplyPartially(1.f);
        m_hasBeenApplied = true;
    }

    void PassiveEffect::applyPartially(float ratio)
    {
        if(!m_hasBeenApplied)
            EffectSystem::getInstance()->addEffect(shared_from_this());

        onApplyPartially(ratio);
        m_hasBeenApplied = true;
    }

    void PassiveEffect::unapply()
    {
        EffectSystem::getInstance()->removeEffect(shared_from_this());
        onUnapply();
        m_hasBeenApplied = false;
    }
}

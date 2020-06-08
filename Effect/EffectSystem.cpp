#include "EffectSystem.h"

#include "AttributeEffect.h"
#include <QDebug>

namespace ItemSystem
{
    std::shared_ptr<EffectSystem> EffectSystem::m_instance = nullptr;

    EffectSystem::EffectSystem()
    {
        std::shared_ptr<AttributeEffect> dummyEffect = std::make_shared<AttributeEffect>(nullptr, "", 0.f, "");
        addEffect(dummyEffect);
    }

    EffectSystem::~EffectSystem()
    {
    }

    std::shared_ptr<EffectSystem> EffectSystem::getInstance()
    {
        if (m_instance == nullptr)
            m_instance = std::shared_ptr<EffectSystem>(new EffectSystem());
        return m_instance;
    }

    void EffectSystem::update(float deltaTime)
    {
        for(auto effect : m_effects)
            effect->update(deltaTime);
    }

    void EffectSystem::addEffect(std::shared_ptr<Effect> effect)
    {
        m_effects.append(effect);
    }

    bool EffectSystem::removeEffect(std::shared_ptr<Effect> effect)
    {
        bool removed = m_effects.removeOne(effect);
        return removed;
    }

    const QList<std::shared_ptr<Effect>>& EffectSystem::getEffects()
    {
        return m_effects;
    }
}

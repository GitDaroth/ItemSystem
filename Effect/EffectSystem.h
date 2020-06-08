#pragma once

#include "Effect.h"

#include <QList>

namespace ItemSystem
{
    class EffectSystem
    {
    public:
        ~EffectSystem();

        static std::shared_ptr<EffectSystem> getInstance();

        void update(float deltaTime);

        void addEffect(std::shared_ptr<Effect> effect);
        bool removeEffect(std::shared_ptr<Effect> effect);
        const QList<std::shared_ptr<Effect>>& getEffects();

    private:
        EffectSystem();

        static std::shared_ptr<EffectSystem> m_instance;
        QList<std::shared_ptr<Effect>> m_effects;
    };
}

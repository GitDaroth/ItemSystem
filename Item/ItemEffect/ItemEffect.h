#pragma once

#include "ItemEffectTemplate.h"
#include "../../Effect/Effect.h"

#include <QRandomGenerator>

namespace ItemSystem
{
    class ItemEffect
    {
    public:
        ItemEffect(std::shared_ptr<ItemEffectTemplate> itemEffectTemplate);
        virtual ~ItemEffect();

        void apply(std::shared_ptr<EffectTarget> target);
        virtual void randomize() = 0;
        virtual std::shared_ptr<Effect> createEffect(std::shared_ptr<EffectTarget> target) = 0;

        QString getTypeTag() const;

    protected:
        std::shared_ptr<ItemEffectTemplate> m_itemEffectTemplate;
        QRandomGenerator m_randomGenerator;
    };
}

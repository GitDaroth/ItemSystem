#include "ItemOverTimeEffect.h"

#include "../../Effect/OverTimeEffect.h"

namespace ItemSystem
{
    ItemOverTimeEffect::ItemOverTimeEffect(std::shared_ptr<ItemEffectTemplate> itemEffectTemplate) :
        ItemTimedEffect(itemEffectTemplate),
        m_itemOverTimeEffectTemplate(std::dynamic_pointer_cast<ItemOverTimeEffectTemplate>(itemEffectTemplate))
    {
        Q_CHECK_PTR(m_itemOverTimeEffectTemplate);
    }

    ItemOverTimeEffect::~ItemOverTimeEffect()
    {
    }

    float ItemOverTimeEffect::getUpdateInterval() const
    {
        return m_itemOverTimeEffectTemplate->getUpdateInterval();
    }

    std::shared_ptr<Effect> ItemOverTimeEffect::createEffect(std::shared_ptr<EffectTarget> target)
    {
        return std::make_shared<OverTimeEffect>(target, getUpdateInterval(), m_duration, createPassiveEffects(target));
    }
}

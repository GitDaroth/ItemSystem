#include "ItemTemporalEffect.h"

#include "../../Effect/TemporalEffect.h"

namespace ItemSystem
{
    ItemTemporalEffect::ItemTemporalEffect(std::shared_ptr<ItemEffectTemplate> itemEffectTemplate) :
        ItemTimedEffect(itemEffectTemplate),
        m_itemTemporalEffectTemplate(std::dynamic_pointer_cast<ItemTemporalEffectTemplate>(itemEffectTemplate))
    {
        Q_CHECK_PTR(m_itemTemporalEffectTemplate);
    }

    ItemTemporalEffect::~ItemTemporalEffect()
    {
    }

    std::shared_ptr<Effect> ItemTemporalEffect::createEffect(std::shared_ptr<EffectTarget> target)
    {
        return std::make_shared<TemporalEffect>(target, m_duration, createPassiveEffects(target));
    }
}

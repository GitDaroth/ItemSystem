#include "ItemPassiveEffect.h"

namespace ItemSystem
{
    ItemPassiveEffect::ItemPassiveEffect(std::shared_ptr<ItemEffectTemplate> itemEffectTemplate) :
        ItemEffect(itemEffectTemplate),
        m_itemPassiveEffectTemplate(std::dynamic_pointer_cast<ItemPassiveEffectTemplate>(itemEffectTemplate)),
        m_passiveEffect(nullptr)
    {
        Q_CHECK_PTR(m_itemPassiveEffectTemplate);
    }

    ItemPassiveEffect::~ItemPassiveEffect()
    {
    }

    void ItemPassiveEffect::unapply()
    {
        if(!m_passiveEffect)
            return;

        m_passiveEffect->unapply();
        m_passiveEffect = nullptr;
    }

    std::shared_ptr<Effect> ItemPassiveEffect::createEffect(std::shared_ptr<EffectTarget> target)
    {
        m_passiveEffect = createPassiveEffect(target);
        return m_passiveEffect;
    }
}

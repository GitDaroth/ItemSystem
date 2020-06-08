#include "ItemEffect.h"

namespace ItemSystem
{
    ItemEffect::ItemEffect(std::shared_ptr<ItemEffectTemplate> itemEffectTemplate) :
        m_itemEffectTemplate(itemEffectTemplate)
    {
        m_randomGenerator = QRandomGenerator::securelySeeded();
    }

    ItemEffect::~ItemEffect()
    {
    }

    void ItemEffect::apply(std::shared_ptr<EffectTarget> target)
    {
        auto effect = createEffect(target);
        effect->apply();
    }

    QString ItemEffect::getTypeTag() const
    {
        return m_itemEffectTemplate->getTypeTag();
    }
}

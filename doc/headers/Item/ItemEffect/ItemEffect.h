/** @defgroup item_effect_group ItemEffect
 *  @ingroup item_group
 *
 *  ItemEffects are extensible. In order to do this you need to inherit from ItemEffect, ItemEffectTemplate and Effect classes.
 *
 *  <b>ItemEffects overview</b><br>
 *  <img src="../images/item_effects_overview_sw.png">
 *
 *  <br>
 *  <b>ItemEffectTemplates</b><br>
 *  <img src="../images/item_effect_templates_sw.png">
 *
 *  <br>
 *  <b>ItemEffects</b><br>
 *  <img src="../images/item_effects_sw.png">
 */

#pragma once

#include "ItemEffectTemplate.h"
#include "../../Effect/Effect.h"

#include <QRandomGenerator>

namespace ItemSystem
{
    /**
    *  @ingroup item_effect_group
    *  @brief Responsible for creating and applying an Effect
    */
    class ItemEffect
    {
    public:
        ItemEffect(std::shared_ptr<ItemEffectTemplate> itemEffectTemplate);
        virtual ~ItemEffect();

        void apply(std::shared_ptr<EffectTarget> target);
        /**
        *  @brief Pure virtual method for randomizing specific class attributes (ex. random duration value between 10s and 20s)
        */
        virtual void randomize() = 0;
        virtual std::shared_ptr<Effect> createEffect(std::shared_ptr<EffectTarget> target) = 0;

        QString getTypeTag() const;

    protected:
        std::shared_ptr<ItemEffectTemplate> m_itemEffectTemplate;
        QRandomGenerator m_randomGenerator;
    };
}

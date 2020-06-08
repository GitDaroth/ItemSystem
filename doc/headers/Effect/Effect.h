/** @defgroup effect Effect
 *
 *  Effects are only used internally. In order to extend Effects you need to subclass Effect, ItemEffect and ItemEffectTemplate.<br>
 *  Only the combination of these three classes works for Effects on Items
 *
 *  <b>Effect module</b><br>
 *  <img src="../images/effects_sw.png">
 */

#pragma once

#include "EffectTarget.h"

#include <memory>

namespace ItemSystem
{
    /**
    *  @ingroup effect
    *  @brief Responsible for applying and updating the Effect
    */
    class Effect : public std::enable_shared_from_this<Effect>
    {
    public:
        explicit Effect(std::shared_ptr<EffectTarget> target);
        virtual ~Effect();

        virtual void update(float deltaTime) = 0;
        void apply();

    protected:
        virtual void onApply() = 0;

        std::shared_ptr<EffectTarget> m_target;
    };
}

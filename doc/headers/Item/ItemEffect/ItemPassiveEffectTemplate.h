#pragma once

#include "ItemEffectTemplate.h"

namespace ItemSystem
{
	/**
	*  @ingroup item_effect_group
	*/
    class ItemPassiveEffectTemplate : public ItemEffectTemplate
    {
    public:
        ItemPassiveEffectTemplate(const QString& typeTag);
        virtual ~ItemPassiveEffectTemplate();
    };
}

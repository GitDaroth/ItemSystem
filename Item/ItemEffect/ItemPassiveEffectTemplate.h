#pragma once

#include "ItemEffectTemplate.h"

namespace ItemSystem
{
    class ItemPassiveEffectTemplate : public ItemEffectTemplate
    {
    public:
        ItemPassiveEffectTemplate(const QString& typeTag);
        virtual ~ItemPassiveEffectTemplate();
    };
}

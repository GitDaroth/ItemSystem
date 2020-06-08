#pragma once

#include "../Template.h"

#include <QJsonObject>

namespace ItemSystem
{
    /**
    *  @ingroup item_effect_group
    *  @brief Used as a blueprint for ItemEffects of the same type
    */
    class ItemEffectTemplate : public Template
    {
    public:
        ItemEffectTemplate(const QString& typeTag);
        virtual ~ItemEffectTemplate();

        QString getTypeTag() const;

    protected:
        QString m_typeTag;
    };
}

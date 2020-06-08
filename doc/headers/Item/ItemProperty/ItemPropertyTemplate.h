#pragma once

#include "../Template.h"

#include <QString>

namespace ItemSystem
{
    /**
    *  @ingroup item_prop_group
    *  @brief Used as a blueprint for ItemProperties
    */
    class ItemPropertyTemplate : public Template
    {
    public:
        ItemPropertyTemplate(const QString& typeTag);
        virtual ~ItemPropertyTemplate();

        QString getTypeTag() const;

    protected:
        QString m_typeTag;
    };
}

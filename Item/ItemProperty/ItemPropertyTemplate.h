#pragma once

#include "../Template.h"

#include <QString>

namespace ItemSystem
{
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

#pragma once

#include "../Template.h"

#include <QJsonObject>

namespace ItemSystem
{
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

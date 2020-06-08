#include "ItemEffectTemplate.h"

namespace ItemSystem
{
    ItemEffectTemplate::ItemEffectTemplate(const QString& typeTag) :
        m_typeTag(typeTag)
    {
    }

    ItemEffectTemplate::~ItemEffectTemplate()
    {
    }

    QString ItemEffectTemplate::getTypeTag() const
    {
        return m_typeTag;
    }
}

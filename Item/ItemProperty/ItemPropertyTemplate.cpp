#include "ItemPropertyTemplate.h"

namespace ItemSystem
{
    ItemPropertyTemplate::ItemPropertyTemplate(const QString& typeTag) :
        m_typeTag(typeTag)
    {
    }

    ItemPropertyTemplate::~ItemPropertyTemplate()
    {
    }

    QString ItemPropertyTemplate::getTypeTag() const
    {
        return m_typeTag;
    }
}

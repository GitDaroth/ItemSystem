#include "ItemProperty.h"

namespace ItemSystem
{
    ItemProperty::ItemProperty(std::shared_ptr<Item> item, std::shared_ptr<ItemPropertyTemplate> propertyTemplate) :
        m_item(item),
        m_propertyTemplate(propertyTemplate)
    {
    }

    ItemProperty::~ItemProperty()
    {
    }

    QString ItemProperty::getTypeTag() const
    {
        return m_propertyTemplate->getTypeTag();
    }
}

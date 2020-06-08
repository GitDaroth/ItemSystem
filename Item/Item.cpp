#include "Item.h"

#include "ItemProperty/ItemPropertyFactory.h"

namespace ItemSystem
{
    Item::Item(const unsigned int instanceId, std::shared_ptr<ItemTemplate> itemTemplate) :
        m_instanceId(instanceId),
        m_template(itemTemplate)
    {
    }

    Item::~Item()
    {
    }

    void Item::initialize()
    {
        for(auto propertyTemplate : m_template->getPropertyTemplates())
        {
            std::shared_ptr<ItemProperty> itemProperty = ItemPropertyFactory::createItemProperty(shared_from_this(), propertyTemplate);
            m_properties.append(itemProperty);
        }
    }

    void Item::initialize(std::shared_ptr<Item> itemToBeCopied)
    {
        for(auto property : itemToBeCopied->getProperties())
            m_properties.append(property->copy());
    }

    void Item::update(float deltaTime)
    {
        for(auto property : m_properties)
            property->update(deltaTime);
    }

    QString Item::getTag() const
    {
        return m_template->getTag();
    }

    QString Item::getName() const
    {
        return m_template->getName();
    }

    unsigned int Item::getId() const
    {
        return m_instanceId;
    }

    const QList<std::shared_ptr<ItemProperty>>& Item::getProperties() const
    {
        return m_properties;
    }

    std::shared_ptr<ItemTemplate> Item::getTemplate()
    {
        return m_template;
    }
}

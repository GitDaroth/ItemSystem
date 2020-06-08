#include "AttributeSystem.h"

#include "../Character/Character.h"

namespace ItemSystem
{
    AttributeSystem::AttributeSystem(std::shared_ptr<Character> character) :
        CharacterComponent(character)
    {
    }

    AttributeSystem::~AttributeSystem()
    {
    }

    void AttributeSystem::update(float deltaTime)
    {
        for (auto attribute : m_attributes)
            attribute->update(deltaTime);
    }

    void AttributeSystem::addAttribute(std::shared_ptr<Attribute> attribute)
    {
        m_attributes.append(attribute);
    }

    bool AttributeSystem::removeAttribute(const QString& attributeTag)
    {
        for (auto attribute : m_attributes)
        {
            if (attribute->getTag() == attributeTag)
            {
                return m_attributes.removeOne(attribute);
            }
        }
        return false;
    }

    bool AttributeSystem::hasAttribute(const QString& attributeTag)
    {
        for (auto attribute : m_attributes)
        {
            if (attribute->getTag() == attributeTag)
                return true;
        }
        return false;
    }

    std::shared_ptr<Attribute> AttributeSystem::getAttribute(const QString& attributeTag)
    {
        for (auto attribute : m_attributes)
        {
            if (attribute->getTag() == attributeTag)
                return attribute;
        }
        return nullptr;
    }

    const QList<std::shared_ptr<Attribute>>& AttributeSystem::getAttributes()
    {
        return m_attributes;
    }
}

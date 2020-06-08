#include "Character.h"

namespace ItemSystem
{
    Character::Character(unsigned int id) :
        m_id(id)
    {
    }

    Character::~Character()
    {
    }

    void Character::update(float deltaTime)
    {
        for (auto component : m_components)
            component->update(deltaTime);
    }

    void Character::addComponent(std::shared_ptr<CharacterComponent> component)
    {
        m_components.append(component);
    }

    bool Character::removeComponent(std::shared_ptr<CharacterComponent> component)
    {
        return m_components.removeOne(component);
    }

    const QList<std::shared_ptr<CharacterComponent>>& Character::getComponents() const
    {
        return m_components;
    }
}

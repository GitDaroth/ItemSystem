/** @defgroup character Character
 *
 *  A Character is simply a container of CharacterComponents and may be freely extended.
 *
 *  @code{.cpp}
 *  unsigned long id = 1;
 *  auto playerCharacter = new Character(id);
 *  auto customCharacterComponent = new CustomCharacterComponent(playerCharacter)
 *  playerCharacter->addComponent(customCharacterComponent);
 *  @endcode
 *
 *  <b>Character module</b><br>
 *  <img src="../images/character_sw.png">
 */ 

#pragma once

#include "../Effect/EffectTarget.h"
#include "CharacterComponent.h"

#include <QList>
#include <memory>

namespace ItemSystem
{
    /**
    *  @ingroup character
    *  @brief Consists of multiple CharacterComponents
    */
    class Character : public EffectTarget
    {
    public:
        Character(unsigned int id);
        virtual ~Character();

        virtual void update(float deltaTime) override;

        void addComponent(std::shared_ptr<CharacterComponent> component);
        bool removeComponent(std::shared_ptr<CharacterComponent> component);

        template<typename ComponentType>
        bool hasComponent() const
        {
            static_assert(std::is_base_of<CharacterComponent, ComponentType>::value, "ComponentType must inherit from CharacterComponent!");
            for (std::shared_ptr<CharacterComponent> component : m_components)
            {
                if (std::dynamic_pointer_cast<ComponentType>(component))
                    return true;
            }
            return false;
        }

        template<typename ComponentType>
        std::shared_ptr<ComponentType> getComponent() const
        {
            static_assert(std::is_base_of<CharacterComponent, ComponentType>::value, "ComponentType must inherit from CharacterComponent!");
            for (std::shared_ptr<CharacterComponent> component : m_components)
            {
                if (std::dynamic_pointer_cast<ComponentType>(component))
                    return std::dynamic_pointer_cast<ComponentType>(component);
            }
            return nullptr;
        }

        const QList<std::shared_ptr<CharacterComponent>>& getComponents() const;

    protected:
        unsigned int m_id;
        QList<std::shared_ptr<CharacterComponent>> m_components;
    };
}

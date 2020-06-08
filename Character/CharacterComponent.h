#pragma once

#include <memory>

namespace ItemSystem
{
    class Character;

    class CharacterComponent
    {
    public:
        CharacterComponent(std::shared_ptr<Character> character);
        virtual ~CharacterComponent();
        virtual void update(float deltaTime) = 0;

        std::shared_ptr<Character> getCharacter();

    protected:
        std::shared_ptr<Character> m_character;
    };
}

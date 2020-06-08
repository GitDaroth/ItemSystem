#include "CharacterComponent.h"

#include "Character.h"

namespace ItemSystem
{
    CharacterComponent::CharacterComponent(std::shared_ptr<Character> character) :
        m_character(character)
    {
    }

    CharacterComponent::~CharacterComponent()
    {
    }

    std::shared_ptr<Character> CharacterComponent::getCharacter()
    {
        return m_character;
    }
}

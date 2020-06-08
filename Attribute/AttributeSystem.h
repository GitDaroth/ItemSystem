#pragma once

#include "../Character/CharacterComponent.h"
#include "Attribute.h"

#include <QList>
#include <memory>

namespace ItemSystem
{
    class AttributeSystem : public CharacterComponent
    {
    public:
        AttributeSystem(std::shared_ptr<Character> character);
        ~AttributeSystem();

        virtual void update(float deltaTime) override;

        void addAttribute(std::shared_ptr<Attribute> attribute);
        bool removeAttribute(const QString& attributeTag);

        bool hasAttribute(const QString& attributeTag);
        std::shared_ptr<Attribute> getAttribute(const QString& attributeTag);
        const QList<std::shared_ptr<Attribute>>& getAttributes();

    private:
        QList<std::shared_ptr<Attribute>> m_attributes;
    };
}

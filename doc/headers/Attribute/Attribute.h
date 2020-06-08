/** @defgroup attribute Attribute
 *
 *  The AttributeSystem is simple to use. You can create a new Attribute by specifying the attribute name and tag. <br>
 *  ResourceAttributes additionaly take in a TraitAttribute that limits the resource. Furthermore, the minimal and base value of the attributes may be set. <br>
 *  <br>
 *  In order to update the Attributes they need to be added to the AttributeSystem.<br>
 *  The AttributeSystem itself is a CharacterCompoenent which needs to be added to a Character.
 *
 *  @code{.cpp}
 *  unsigned long id = 1;
 *  auto playerCharacter = new Character(id);
 *
 *  auto attributeSystem = new AttributeSystem();
 *  auto attackDamageAttribute = new TraitAttribute("attack_damage", "Attack Damage");
 *  auto maxHealthAttribute = new TraitAttribute("max_health", "Max. Health");
 *  auto healthAttribute = new ResourceAttribute("health", "Health", maxHealthAttribute);
 *  auto maxManaAttribute = new TraitAttribute("max_mana", "Max. Mana");
 *  auto manaAttribute = new ResourceAttribute("mana", "Mana", maxManaAttribute);
 *  attributeSystem->addAttribute(attackDamageAttribute);
 *  attributeSystem->addAttribute(maxHealthAttribute);
 *  attributeSystem->addAttribute(healthAttribute);
 *  attributeSystem->addAttribute(maxManaAttribute);
 *  attributeSystem->addAttribute(manaAttribute);
 *
 *  playerCharacter->addComponent(attributeSystem);
 *  @endcode
 *
 *  <b>Attribute module</b><br>
 *  <img src="../images/attributes_sw.png">
 */ 

#pragma once

#include <QString>

namespace ItemSystem
{
    /**
    *  @ingroup attribute
    *  @brief Encapsulates the value and method for the Attribute modification
    */
    struct AttributeModifier
    {
        AttributeModifier(float value, const QString& method)
        {
            this->value = value;
            this->method = method;
        }

        float value;
        /**
        *  @brief Modification method as string (ex. additive, multiplicative, ...)
        */
        QString method;
    };

    /**
    *  @ingroup attribute
    */
    class Attribute
    {
    public:
        Attribute(const QString& tag, const QString& name);
        virtual ~Attribute();

        virtual void update(float deltaTime) = 0;
        virtual void applyModifier(const AttributeModifier& modifier) = 0;
        /**
        *  @brief Pure virtual method that returns the total/final attribute value under consideration of the modifiers
        */
        virtual float getFinalValue() const = 0;

        QString getTag() const;
        QString getName() const;
        float getMinValue() const;
        float getBaseValue() const;

        void setMinValue(float minValue);
        void setBaseValue(float baseValue);

    protected:
        virtual float clampValue(float value) const = 0;

        QString m_tag;
        QString m_name;
        float m_baseValue;
        float m_minValue;
    };
}

/** @defgroup item_prop_group ItemProperty
 *  @ingroup item_group
 *
 *  ItemProperties are extensible. You only need to inherit from ItemProperty and ItemPropertyTemplate.
 *
 *  <b>Preimplemented StackableProp</b><br>
 *  <img src="../images/stackable_prop_sw.png">
 *
 *  <br>
 *  <b>Preimplemented ConsumableProp</b><br>
 *  <img src="../images/consumable_prop_sw.png">
 *
 *  <br>
 *  <b>Preimplemented EquipableProp</b><br>
 *  <img src="../images/equipable_prop_sw.png">
 */

#pragma once

#include "ItemPropertyTemplate.h"
#include "../Item.h"

#include <memory>

namespace ItemSystem
{
    /**
    *  @ingroup item_prop_group
    *  @brief ItemProperty is a type object of ItemPropertyTemplate
    */
    class ItemProperty
    {
    public:
        ItemProperty(std::shared_ptr<Item> item, std::shared_ptr<ItemPropertyTemplate> propertyTemplate);
        virtual ~ItemProperty();

        virtual std::shared_ptr<ItemProperty> copy() const = 0;
        virtual void update(float deltaTime) = 0;

        QString getTypeTag() const;

    protected:
        std::shared_ptr<Item> m_item;
        std::shared_ptr<ItemPropertyTemplate> m_propertyTemplate;
    };
}

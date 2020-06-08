/** @defgroup item_container Item Container
 *
 *  An ItemContainer is just a collection of Items.<br>
 *  You need to inherit from ItemContainer in order to use it because the methode "triggerItem" is pure virtual and needs to be implemented.<br>
 *  The ItemInventory class is a special ItemContainer that has multiple EquipmentSlots.<br>
 *  Such an EquipmentSlot is determined by an ItemCondition and needs to be defined in a JSON file.
 *
 *  @code{.cpp}
 *  [
 *      {"equipment_slot":{
 *              "tag": "weapon_slot",
 *              "item_category_condition":{
 *                      "operator": "equal",
 *                      "value": "weapon"
 *              }
 *      }},
 *      {"equipment_slot":{
 *              "tag": "armor_slot",
 *              "item_category_condition":{
 *                      "operator": "equal",
 *                      "value": "armor"
 *              }
 *      }}
 *  ]
 *  @endcode
 *
 *  Example usage of an custom ItemInventory
 *
 *  @code{.cpp}
 *  unsigned long id = 1;
 *  auto playerCharacter = new Character(id);
 *
 *  auto inventory = new CustomInventory(playerCharacter);
 *  inventory->readEquipmentSlots("equipmentSlots.json");
 *  playerCharacter->addComponent(inventory);
 *
 *  auto dragonSlayerItem = ItemFactory::createItem("dragon_slayer");
 *  inventory->addItem(dragonSlayerItem);
 *  unsigned int itemIndex = 0;
 *  inventory->triggerItem(itemIndex, "right_click");
 *  @endcode
 *
 *  <b>Character module</b><br>
 *  <img src="../images/item_container_sw.png">
 */

#pragma once

#include "../Item/Item.h"

namespace ItemSystem
{
    /**
    *  @ingroup item_container
    *  @brief A simple Container of Items with a specified capacity
    */
    class ItemContainer
    {
    public:
        ItemContainer(unsigned int capacity);
        virtual ~ItemContainer();

        /**
        *  @brief Pure virtual method that defines the behaviour when interacting with an Item in the ItemContainer (ex. right click, ...)
        *
        *  @param index The Item index in the ItemContainer
        *  @param inputType A String specified the interaction (ex. right click, button 'R' pressed, ...)
        */
        virtual void triggerItem(unsigned int index, const QString& inputType) = 0;

        bool addItem(std::shared_ptr<Item> item);
        bool removeItem(std::shared_ptr<Item> item);
        bool removeItemById(unsigned int itemId);
        void removeAllItems();

        const QList<std::shared_ptr<Item>>& getItems();
        unsigned int getItemCount() const;
        unsigned int getCapacity() const;
        void setCapacity(unsigned int capacity);

    protected:
        unsigned int m_capacity;
        QList<std::shared_ptr<Item>> m_items;
    };
}

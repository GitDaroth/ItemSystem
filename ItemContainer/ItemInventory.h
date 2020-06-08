#pragma once

#include "ItemContainer.h"
#include "EquipmentSlot.h"
#include "../Character/CharacterComponent.h"

namespace ItemSystem
{
    class ItemInventory : public ItemContainer, public CharacterComponent
    {
    public:
        ItemInventory(unsigned int capacity, std::shared_ptr<Character> character);
        virtual ~ItemInventory();

        virtual void update(float deltaTime) override;
        void readEquipmentSlots(const QString& filePath);

        std::shared_ptr<EquipmentSlot> findEquipmentSlotForItem(std::shared_ptr<Item> item);
        std::shared_ptr<EquipmentSlot> findEquipmentSlotByTag(const QString& tag);

    protected:
        QList<std::shared_ptr<EquipmentSlot>> m_equipmentSlots;
    };
}

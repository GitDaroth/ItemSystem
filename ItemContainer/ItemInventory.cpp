#include "ItemInventory.h"

#include "../Character/Character.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QtGlobal>

namespace ItemSystem
{
    ItemInventory::ItemInventory(unsigned int capacity, std::shared_ptr<Character> character) :
        ItemContainer(capacity),
        CharacterComponent(character)
    {
    }

    ItemInventory::~ItemInventory()
    {
    }

    void ItemInventory::update(float deltaTime)
    {
        for(auto item : m_items)
            item->update(deltaTime);
    }

    void ItemInventory::readEquipmentSlots(const QString& filePath)
    {
        QFile file(filePath);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString jsonString = file.readAll();
        file.close();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());

        Q_ASSERT(jsonDoc.isArray());
        QJsonArray slotsJsonArray = jsonDoc.array();
        for (QJsonValue slotWrapperJsonValue : slotsJsonArray)
        {
            Q_ASSERT(slotWrapperJsonValue.isObject());
            QJsonObject slotWrapperJsonObject = slotWrapperJsonValue.toObject();

            QJsonValue slotJsonValue = slotWrapperJsonObject.value("equipment_slot");
            Q_ASSERT(slotJsonValue.isObject());
            QJsonObject slotJsonObject = slotJsonValue.toObject();

            m_equipmentSlots.append(std::make_shared<EquipmentSlot>(slotJsonObject));
        }
    }

    std::shared_ptr<EquipmentSlot> ItemInventory::findEquipmentSlotForItem(std::shared_ptr<Item> item)
    {
        for(auto equipmentSlot : m_equipmentSlots)
        {
            if(equipmentSlot->doesItemFit(item))
                return equipmentSlot;
        }
        return nullptr;
    }

    std::shared_ptr<EquipmentSlot> ItemInventory::findEquipmentSlotByTag(const QString& tag)
    {
        for(auto equipmentSlot : m_equipmentSlots)
        {
            if(equipmentSlot->getTag() == tag)
                return equipmentSlot;
        }
        return nullptr;
    }
}

#include "EquipmentSlot.h"

#include "../ItemCondition/ItemConditionFactory.h"

#include <QtGlobal>

namespace ItemSystem
{
    EquipmentSlot::EquipmentSlot(const QJsonObject& jsonObject) :
        m_item(nullptr)
    {
        read(jsonObject);
    }

    EquipmentSlot::~EquipmentSlot()
    {
    }

    std::shared_ptr<Item> EquipmentSlot::insertItem(std::shared_ptr<Item> item)
    {
        if(doesItemFit(item))
        {
            std::shared_ptr<Item> oldItem = takeItem();
            m_item = item;
            return oldItem;
        }

        return nullptr;
    }

    std::shared_ptr<Item> EquipmentSlot::takeItem()
    {
        std::shared_ptr<Item> item = m_item;
        m_item = nullptr;
        return item;
    }

    std::shared_ptr<Item> EquipmentSlot::getItem()
    {
        return m_item;
    }

    bool EquipmentSlot::doesItemFit(std::shared_ptr<Item> item) const
    {
        return m_itemCondition->evaluate(item->getTemplate());
    }

    bool EquipmentSlot::isEmpty() const
    {
        return (m_item == nullptr);
    }

    QString EquipmentSlot::getTag() const
    {
        return m_tag;
    }

    void EquipmentSlot::read(const QJsonObject& jsonObject)
    {
        readTag(jsonObject);
        readItemCondition(jsonObject);
    }

    void EquipmentSlot::readTag(const QJsonObject& jsonObject)
    {
        QJsonValue tagJsonValue = jsonObject.value("tag");
        Q_ASSERT(tagJsonValue.isString());
        m_tag = tagJsonValue.toString();
    }

    void EquipmentSlot::readItemCondition(const QJsonObject& jsonObject)
    {
        Q_ASSERT(jsonObject.keys().size() == 2);
        QString itemConditionType;
        for(QString key : jsonObject.keys())
        {
            if(key != "tag")
                itemConditionType = key;
        }

        QJsonValue itemConditionJsonValue = jsonObject.value(itemConditionType);
        Q_ASSERT(itemConditionJsonValue.isObject());
        QJsonObject itemConditionJsonObject = itemConditionJsonValue.toObject();

        m_itemCondition = ItemConditionFactory::createItemCondition(itemConditionType, itemConditionJsonObject);
    }
}

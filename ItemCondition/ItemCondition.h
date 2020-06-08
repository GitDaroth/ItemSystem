#pragma once

#include "../Item/ItemTemplate.h"

#include <functional>

namespace ItemSystem
{
    class ItemCondition
    {
    public:
        ItemCondition(const QString& typeTag);
        virtual ~ItemCondition();

        void read(const QJsonObject& conditionJsonObject);
        virtual void onRead(const QJsonObject& conditionJsonObject) = 0;
        virtual bool evaluate(std::shared_ptr<ItemTemplate> itemTemplate) = 0;

        QString getTypeTag() const;

    protected:
        virtual void initOperatorFunction() = 0;

        QString m_typeTag;
        QString m_operator;

    private:
        void readOperator(const QJsonObject& conditionJsonObject);
    };
}

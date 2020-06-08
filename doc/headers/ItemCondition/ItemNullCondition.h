#pragma once

#include "ItemCondition.h"

namespace ItemSystem
{
    /**
    *  @ingroup item_condition
    *  @brief This ItemCondition always matches
    */
    class ItemNullCondition : public ItemCondition
    {
    public:
        ItemNullCondition(const QString& typeTag);
        virtual ~ItemNullCondition();

        virtual void onRead(const QJsonObject& conditionJsonObject) override;
        virtual bool evaluate(std::shared_ptr<ItemTemplate> itemTemplate) override;

    protected:
        virtual void initOperatorFunction() override;
    };
}

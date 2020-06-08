#pragma once

#include "ItemCondition.h"

namespace ItemSystem
{
    class ItemConditionChain : public ItemCondition
    {
    public:
        ItemConditionChain(const QString& typeTag);
        virtual ~ItemConditionChain();

        virtual void onRead(const QJsonObject& conditionJsonObject) override;
        virtual bool evaluate(std::shared_ptr<ItemTemplate> itemTemplate) override;

    protected:
        virtual void initOperatorFunction() override;

        QList<std::shared_ptr<ItemCondition>> m_chainedConditions;
        std::function<bool(bool, bool)> m_operatorFunction;

    private:
        void readChainedConditions(const QJsonObject& conditionJsonObject);
    };
}

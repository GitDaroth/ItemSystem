#pragma once

#include "ItemCondition.h"

namespace ItemSystem
{
    /**
    *  @ingroup item_condition
    *  @brief Handles comparisons with integer values with the corresponding operators
    */
    class ItemIntegerCondition : public ItemCondition
    {
    public:
        ItemIntegerCondition(const QString& typeTag);
        virtual ~ItemIntegerCondition();

        virtual void onRead(const QJsonObject& conditionJsonObject) override;

    protected:
        virtual void initOperatorFunction() override;

        int m_value;
        std::function<bool(int, int)> m_operatorFunction;

    private:
        void readValue(const QJsonObject& conditionJsonObject);
    };
}

#pragma once

#include "ItemCondition.h"

namespace ItemSystem
{
    class ItemStringCondition : public ItemCondition
    {
    public:
        ItemStringCondition(const QString& typeTag);
        virtual ~ItemStringCondition();

        virtual void onRead(const QJsonObject& conditionJsonObject) override;

    protected:
        virtual void initOperatorFunction() override;

        QString m_value;
        std::function<bool(QString, QString)> m_operatorFunction;

    private:
        void readValue(const QJsonObject& conditionJsonObject);
    };
}

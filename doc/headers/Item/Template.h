#pragma once

#include <QJsonObject>

namespace ItemSystem
{
    /**
    *  @ingroup item_group
    *  @brief Interface for all Templates that need to read in data from JsonObjects
    */
    class Template
    {
    public:
        virtual void read(const QJsonObject& jsonObject) = 0;
    };
}

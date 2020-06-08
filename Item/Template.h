#pragma once

#include <QJsonObject>

namespace ItemSystem
{
    class Template
    {
    public:
        virtual void read(const QJsonObject& jsonObject) = 0;
    };
}

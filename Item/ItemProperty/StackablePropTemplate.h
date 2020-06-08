#pragma once

#include "ItemPropertyTemplate.h"

namespace ItemSystem
{
    class StackablePropTemplate : public ItemPropertyTemplate
    {
    public:
        StackablePropTemplate(const QString& typeTag);
        virtual ~StackablePropTemplate();

        virtual void read(const QJsonObject& jsonObject) override;

        unsigned int getMaxStacks() const;

    protected:
        unsigned int m_maxStacks;
    };
}

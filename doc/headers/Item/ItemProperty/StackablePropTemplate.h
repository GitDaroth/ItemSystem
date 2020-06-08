#pragma once

#include "ItemPropertyTemplate.h"

namespace ItemSystem
{
    /**
    *  @ingroup item_prop_group
    *  @brief ItemPropertyTemplate that reads in the shared data
    */
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

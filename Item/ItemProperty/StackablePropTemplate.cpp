#include "StackablePropTemplate.h"

#include <QJsonValue>
#include <QtGlobal>

namespace ItemSystem
{
    StackablePropTemplate::StackablePropTemplate(const QString& typeTag) :
        ItemPropertyTemplate(typeTag)
    {
    }

    StackablePropTemplate::~StackablePropTemplate()
    {
    }

    void StackablePropTemplate::read(const QJsonObject& jsonObject)
    {
        QJsonValue stackJsonValue = jsonObject.value("max_stacks");
        Q_ASSERT(stackJsonValue.isDouble());
        Q_ASSERT((int)stackJsonValue.toDouble() > 0);
        m_maxStacks = (unsigned int)stackJsonValue.toDouble();
    }

    unsigned int StackablePropTemplate::getMaxStacks() const
    {
        return m_maxStacks;
    }
}

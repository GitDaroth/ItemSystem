#include "StackableProp.h"

#include "../ItemFactory.h"
#include "ItemPropertyFactory.h"

#include <QtGlobal>
#include <QtMath>

namespace ItemSystem
{
    StackableProp::StackableProp(std::shared_ptr<Item> item, std::shared_ptr<ItemPropertyTemplate> propertyTemplate) :
        ItemProperty(item, propertyTemplate),
        m_stackablePropTemplate(std::dynamic_pointer_cast<StackablePropTemplate>(propertyTemplate)),
        m_currentStacks(1)
    {
        Q_CHECK_PTR(m_stackablePropTemplate);
    }

    StackableProp::~StackableProp()
    {
    }

    std::shared_ptr<ItemProperty> StackableProp::copy() const
    {
        std::shared_ptr<ItemProperty> copiedProperty = ItemPropertyFactory::createItemProperty(m_item, m_propertyTemplate);
        std::shared_ptr<StackableProp> copiedStackableProp = std::dynamic_pointer_cast<StackableProp>(copiedProperty);
        copiedStackableProp->setCurrentStacks(m_currentStacks);
        return copiedStackableProp;
    }

    void StackableProp::update(float deltaTime)
    {
    }

    void StackableProp::addStacks(unsigned int stacksToAdd)
    {
        m_currentStacks += stacksToAdd;
        clampCurrentStacks();
    }

    void StackableProp::removeStacks(unsigned int stacksToRemove)
    {
        m_currentStacks -= stacksToRemove;
        clampCurrentStacks();
    }

    std::shared_ptr<Item> StackableProp::splitItem(unsigned int stacks)
    {
        if(stacks >= m_currentStacks)
            return nullptr;

        m_currentStacks -= stacks;
        std::shared_ptr<Item> m_splittedItem = ItemFactory::copyItem(m_item);
        m_splittedItem->getProperty<StackableProp>()->setCurrentStacks(stacks);
        return m_splittedItem;
    }

    bool StackableProp::isPossibleToAddStacks(unsigned int stacksToAdd) const
    {
        return (m_currentStacks + stacksToAdd) <= getMaxStacks();
    }

    bool StackableProp::isPossibleToRemoveStacks(unsigned int stacksToRemove) const
    {
        return ((int)m_currentStacks - (int)stacksToRemove) >= (int)m_minStacks;
    }

    bool StackableProp::isFull() const
    {
        return m_currentStacks >= getMaxStacks();
    }

    unsigned int StackableProp::getCurrentStacks() const
    {
        return m_currentStacks;
    }

    unsigned int StackableProp::getMaxStacks() const
    {
        return m_stackablePropTemplate->getMaxStacks();
    }

    void StackableProp::setCurrentStacks(unsigned int stacks)
    {
        m_currentStacks = stacks;
        clampCurrentStacks();
    }

    void StackableProp::clampCurrentStacks()
    {
        m_currentStacks = qMin(qMax(m_currentStacks, m_minStacks), getMaxStacks());
    }
}

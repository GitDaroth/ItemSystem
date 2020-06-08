#pragma once

#include "ItemProperty.h"
#include "StackablePropTemplate.h"

namespace ItemSystem
{
    /**
    *  @ingroup item_prop_group
    *  @brief ItemProperty that manages stacks for an Item
    */
    class StackableProp : public ItemProperty
    {
    public:
        StackableProp(std::shared_ptr<Item> item, std::shared_ptr<ItemPropertyTemplate> propertyTemplate);
        virtual ~StackableProp();

        virtual std::shared_ptr<ItemProperty> copy() const override;
        virtual void update(float deltaTime) override;

        void addStacks(unsigned int stacksToAdd);
        void removeStacks(unsigned int stacksToRemove);

        /**
        *  @brief Splits the stackable Item by removing a specific amount of stacks
        */
        std::shared_ptr<Item> splitItem(unsigned int stacks);

        bool isPossibleToAddStacks(unsigned int stacksToAdd) const;
        bool isPossibleToRemoveStacks(unsigned int stacksToRemove) const;

        bool isFull() const;
        unsigned int getCurrentStacks() const;
        unsigned int getMaxStacks() const;
        void setCurrentStacks(unsigned int stacks);

    protected:
        void clampCurrentStacks();

        std::shared_ptr<StackablePropTemplate> m_stackablePropTemplate;
        const unsigned int m_minStacks = 0;
        unsigned int m_currentStacks;
    };
}

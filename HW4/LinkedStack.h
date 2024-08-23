/**
* 17.05.2024
* @author Barış Pamuksuz
* ID: 22202238
* CS201-HW4
* References
* ----------
* Carrano, Frank M., and Timothy M. Henry. Data Abstraction & Problem Solving with C++: Walls and Mirrors. 7th ed., Pearson, 2016.
*/
#ifndef _LINKEDSTACK__
#define _LINKEDSTACK__

#include "StackInterface.h"
#include "Node.h"

template <class ItemType>
class LinkedStack : public StackInterface<ItemType> {
public:
    Node<ItemType>* topPtr;
    LinkedStack() : topPtr(nullptr) {}

    virtual ~LinkedStack() {
        while (!isEmpty()) {
            pop();
        }
    }
    virtual bool isEmpty() const override {
        return topPtr == nullptr;
    }
    virtual bool push(ItemType newItem) override {
        Node<ItemType>* newNodePtr = new Node<ItemType>(newItem, topPtr);
        topPtr = newNodePtr;
        return true;
    }
    virtual bool pop() override {
        if (!isEmpty()) {
            Node<ItemType>* nodeToDeletePtr = topPtr;
            topPtr = topPtr->getNext();
            delete nodeToDeletePtr;
            return true;
        }
        return false;
    }
    virtual ItemType peek() const override {
        if (!isEmpty()) {
            return topPtr->getItem();
        }
        return topPtr->getItem();
    }
};
#endif

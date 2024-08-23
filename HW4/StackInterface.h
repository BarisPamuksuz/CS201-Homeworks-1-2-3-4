/**
 * 17.05.2024
 * @author Barış Pamuksuz
 * ID: 22202238
 * CS201-HW4
 * References
 * ----------
 * Carrano, Frank M., and Timothy M. Henry. Data Abstraction & Problem Solving with C++: Walls and Mirrors. 7th ed., Pearson, 2016.
 */
#ifndef STACK_INTERFACE__
#define STACK_INTERFACE__

template<class ItemType>
class StackInterface {
public:
    virtual ~StackInterface() {}
    virtual bool isEmpty() const = 0;
    virtual bool push(ItemType newEntry) = 0;
    virtual bool pop() = 0;
    virtual ItemType peek() const = 0;
};

#endif

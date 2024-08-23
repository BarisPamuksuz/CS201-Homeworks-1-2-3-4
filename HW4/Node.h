/**
 * 17.05.2024
 * @author Barış Pamuksuz
 * ID: 22202238
 * CS201-HW4
 * References
 * ----------
 * Carrano, Frank M., and Timothy M. Henry. Data Abstraction & Problem Solving with C++: Walls and Mirrors. 7th ed., Pearson, 2016.
 */
#ifndef _NODE__
#define _NODE__

template<class ItemType>
class Node{
    public:
    
    Node():next(nullptr){};
    Node(const ItemType& anItem):item(anItem),next(nullptr){};
    Node(const ItemType& anItem, Node<ItemType>* nextNodePtr):item(anItem),next(nextNodePtr){};
    
    void setItem(const ItemType& anItem){
    item = anItem;
    }
    void setNext(Node<ItemType>* nextNodePtr){
    next = nextNodePtr;
    }
    ItemType& getItem() {
    return item;
    }
    Node<ItemType>* getNext() const{
    return next;
    }
    private:
    ItemType item;
    Node<ItemType>* next;
};
#endif
template<class ItemType>
class Node {
public:
    Node(const ItemType& anItem):item(anItem),nextPtr(nullptr){}

    void setNext(Node<ItemType>* nextNewPtr){
        nextPtr = nextNewPtr;
    }
    ItemType& getItem(){
        return item;
    }
    Node<ItemType>* getNext() const{
        return nextPtr;
    }
    
private:
    ItemType item;
    Node<ItemType>* nextPtr;
};


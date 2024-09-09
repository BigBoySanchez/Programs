class ItemType {
public:
    ItemType(int number = 0);
private:
    int value;
};

struct NodeType {
    ItemType info;
    NodeType* next;
};

class UnsortedType {
public:
    UnsortedType();
    ~UnsortedType();
    void putItem(ItemType toAdd);                   // put toAdd at the end of list
    void putItem(ItemType toAdd, int position);     // put toAdd at position. does nothing if position invalid
    void deleteItem(int key);                       // delete first item in list with key
    void printAll(NodeType *head) const;            // print list w/ format: 
private:
    NodeType *head;
};
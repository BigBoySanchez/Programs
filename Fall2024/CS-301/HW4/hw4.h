class ItemType {
public:
    ItemType(char info);
    char getInfo() const;

private:
    char info;
};

struct NodeType {
    ItemType info;
    NodeType *prev;
    NodeType *next;

    NodeType(const ItemType& i, NodeType *p = nullptr, NodeType *n = nullptr) :
             info(i), prev(p), next(n) {}

    NodeType *getAt(int dist) {
        NodeType *curr = this;
        
        if(dist > 0) {
            while(dist > 0) {
                curr = curr->next;
                if(!curr) break;

                dist--;
            }
        } else if(dist < 0) {
            while (dist < 0) {
                curr = curr->prev;
                if(!curr) break;

                dist++;
            }
        }

        return curr;
    }
};

class DoubleList {
public:
    DoubleList();
    ~DoubleList();

    NodeType *begin() const;
    NodeType *end() const;

    void putItem(const ItemType& toPut);

private:
    NodeType *head;
    NodeType *tail;
};
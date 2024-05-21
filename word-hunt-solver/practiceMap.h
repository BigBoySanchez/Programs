#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
    
template <typename keyType, typename valType>
class practiceMap {
    private:
    static const unsigned int TABLE_SIZE = 10000;
    struct node {
        keyType key;
        valType val; 
        node * next;
    };
    node * buckets[TABLE_SIZE] = { nullptr };

    //find the node with key (LOW PRIORITY)
    node * findNode(const keyType & key) const;

    public:
    
    //makes empty map
    practiceMap();

    //deletes all nodes in each bucket
    ~practiceMap();

    //return hash for key
    unsigned int getHash(const keyType & toHash) const;

    //return hash for a string
    unsigned int getHash(const string & toHash) const;

    //deletes all nodes in each bucket
    void clear();

    //index into map using key
    valType & operator[](const keyType & key);

    //prints map like: "bucketNum:   {key1, val1}, {key2, val2}\n..."
    friend ostream & operator<<(ostream & out, const practiceMap<keyType, valType> & toPrint);
};
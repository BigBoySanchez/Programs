#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

class Node
{
public:
    int value;
    Node *left, *right;
    Node(int v = 0, Node *l = nullptr, Node *r = nullptr)
    {
        value = v;
        left = l;
        right = r;
    }
};

class OrderedSet
{
private:
    Node *root;
    int size;

    static void drawTree(Node *r, int offset)
    {
        char c = r == nullptr ? '.' : '-';
        for (int i = 0; i < offset; i++)
            cout << ' ';
        for (int i = 0; i < 4; i++)
            cout << c;
        if (r != nullptr)
        {
            cout << r->value << endl;
            offset += 4;
            drawTree(r->left, offset);
            drawTree(r->right, offset);
        }
        else
            cout << '.' << endl;
    }

    // Assume r is not null
    Node *findParent(Node *r, int target, Node *&child) const
    {
        if (r->value == target) // r already contains the target value
        {
            child = r;
            return nullptr;
            // If caller gets back null, then the original r contains target.
        }
        if (r->value > target)
        {
            child = r->left;
            if (child == nullptr || child->value == target)
            {
                return r;
            }
            return findParent(r->left, target, child);
        }
        child = r->right;
        if (child == nullptr || child->value == target)
        {
            return r;
        }
        return findParent(r->right, target, child);
    }

    static bool find2(Node *r, int v)
    {
        if (r == nullptr)
            return false;
        if (r->value == v)
            return true;
        if (find2(r->left, v))
            return true;
        if (find2(r->right, v))
            return true;
        return false;
    }

    static void preorder(Node *r)
    {
        if (r == nullptr)
            return;
        cout << r->value << " ";
        preorder(r->left);
        preorder(r->right);
    }
    static void postorder(Node *r)
    {
        if (r == nullptr)
            return;
        postorder(r->left);
        postorder(r->right);
        cout << r->value << " ";
    }
    static void inorder(Node *r)
    {
        if (r == nullptr)
            return;
        inorder(r->left);
        cout << r->value << " ";
        inorder(r->right);
    }

    static void levelorder(Node *n)
    {

        if (n != nullptr)
        {
            queue<Node *> q;
            q.push(n);
            while (!q.empty())
            {
                Node *temp = q.front();
                cout << temp->value << " ";
                q.pop();
                if (temp->left != nullptr)
                    q.push(temp->left);
                if (temp->right != nullptr)
                    q.push(temp->right);
            }
        }
        cout << endl;
    }

    static Node *makeDegenerateTreeLeft(int a[], int length)
    {
        return length == 0 ? nullptr : new Node(a[length - 1], makeDegenerateTreeLeft(a, length - 1));
    }

    static Node *makeDegenerateTreeRight(int a[], int length)
    {
        return length == 0 ? nullptr : new Node(a[0], nullptr, makeDegenerateTreeRight(a + 1, length - 1));
    }

    static Node *makeDegenerateTreeAlternating(int a[], int length)
    {
        return length == 0 ? nullptr : length % 2 == 0 ? new Node(a[length - 1], makeDegenerateTreeAlternating(a, length - 1))
                                                       : new Node(a[0], nullptr, makeDegenerateTreeAlternating(a + 1, length - 1));
    }

    static Node *makeBalancedTree(int a[], int length)
    {
        if (length == 0)
            return nullptr;

        int leftLen = length / 2, rightLen = (length - 1) / 2, mid = leftLen;

        return new Node(a[mid],
                        makeBalancedTree(a, leftLen),
                        makeBalancedTree(a + leftLen + 1, rightLen));
    }

    static int getSize(Node *r)
    {
        if (r == nullptr)
            return 0;
        return 1 + getSize(r->left) + getSize(r->right);
    }
    static int getHeight(Node *r)
    {
        if (r == nullptr)
            return 0;
        return 1 + max(getHeight(r->left), getHeight(r->right));
    }
    static bool isBalanced(Node *r)
    {
        if (r == nullptr)
            return true;
        int h1 = getHeight(r->left), h2 = getHeight(r->right);
        return h1 <= h2 + 1 && h2 <= h1 + 1 && isBalanced(r->left) && isBalanced(r->right);
    }

    static bool isDegenerate(Node *r)
    {
        return getHeight(r) == getSize(r);
    }

    static void deleteTree(Node *r)
    {
        if (r != nullptr)
        {
            deleteTree(r->left);
            deleteTree(r->right);
            delete r;
        }
    }

    void recursiveToArray(Node *root, int buff[], int& currIdx) {
        if(root == nullptr) return;
        

        //inorder traversal
        recursiveToArray(root->left, buff, currIdx);
        buff[currIdx] = root->value;
        currIdx++;
        recursiveToArray(root->right, buff, currIdx);
    }

public:
    // Remove the value in Node r by replacing it with
    // the smallest value in the right subtree of r.
    // It's assumed that the right subtree is nonempty.
    // Let temp store the address of r->right.
    // If temp->left is null, then just copy the
    // temp->value into r then remove ("bypass and delete") temp.
    // If temp->left is not null, then go left
    // until you reach the parent of the node with smallest value
    // in the left subtree of temp. Copy that smallest value
    // into r, then remove the node that contained it.
    static void removeViaReplace(Node *r)
    {
        Node *temp = r->right;
        if (temp->left == nullptr)
        {
            r->value = temp->value;
            r->right = temp->right;
            delete temp;
        }
        else
        {
            Node *child = temp->left, *parent = temp;
            while (child->left != nullptr)
            {
                parent = child;
                child = child->left;
            }
            r->value = child->value;
            parent->left = child->right;
            delete child;
        }
    }

    OrderedSet()
    {
        root = nullptr;
        size = 0;
    }

    ~OrderedSet()
    {
        deleteTree(root);
    }

    // presumes that a is sorted
    OrderedSet(int a[], int length, int type = 2)
    {
        root =
            type == -1 ? makeDegenerateTreeLeft(a, length) : type == 1 ? makeDegenerateTreeRight(a, length)
                                                         : type == 0   ? makeDegenerateTreeAlternating(a, length)
                                                                       : makeBalancedTree(a, length); // type == 2

        size = length;
    }

    void preorder() const
    {
        preorder(root);
        cout << endl;
    }

    void postorder() const
    {
        postorder(root);
        cout << endl;
    }

    void inorder() const
    {
        inorder(root);
        cout << endl;
    }

    void getSmallest(int &v) const
    {
        if (root != nullptr)
        {
            Node *temp = root;
            while (temp->left != nullptr)
                temp = temp->left;
            v = temp->value;
        }
    }

    void getBiggest(int &v) const
    {
        if (root != nullptr)
        {
            Node *temp = root;
            while (temp->right != nullptr)
                temp = temp->right;
            v = temp->value;
        }
    }

    void levelorder() const
    {

        if (root != nullptr)
        {
            queue<Node *> q;
            q.push(root);
            while (!q.empty())
            {
                Node *temp = q.front();
                cout << temp->value << " ";
                q.pop();
                if (temp->left != nullptr)
                    q.push(temp->left);
                if (temp->right != nullptr)
                    q.push(temp->right);
            }
        }
        cout << endl;
    }

    bool insert(int v)
    {
        if (root == nullptr)
        {
            root = new Node(v);
            size = 1;
            return true;
        }
        Node *c, *p = findParent(root, v, c);
        if (c != nullptr)
            return false;                               // value is already in tree
        Node *&ref = v < p->value ? p->left : p->right; // reference to pointer that needs updating
        ref = new Node(v);
        size++;
        return true;
    }

    // remove v and return true or return false if v not found.
    bool remove(int v)
    {
        if (root == nullptr)
            return false;

        Node *child, *parent = findParent(root, v, child); // get parent info

        if (child == nullptr) // v was not found
            return false;

        if (child->left != nullptr && child->right != nullptr)
            removeViaReplace(child); // replace child's value by minimum value in right subtree
        else
        {
            if (child == root) // v are found in the root
                root = root->left != nullptr ? root->left : root->right;
            else
            {
                // "bypass" child node
                Node *toAttach = child->left != nullptr ? child->left : child->right;
                (parent->left == child ? parent->left : parent->right) = toAttach;
            }
            delete child;
        }
        size--;
        return true;
    }

    // Return true if v is in the set and false otherwise.
    // (If this were a map, we would return the associated object with key v.)
    bool find(int v) const
    {
        if (root == nullptr)
            return false;
        Node *child = nullptr;
        findParent(root, v, child);
        return child != nullptr; // a node was found containing v.
    }

    bool contains(int v)
    {
        return find2(root, v);
    }

    void drawTree() const
    {
        drawTree(root, 0);
    }

    void printInfo() const
    {
        cout << "________________________________________________" << endl;
        cout << "Size = " << size << endl;
        cout << "Height = " << getHeight(root) << endl;
        cout << "Balanced = " << (isBalanced(root) ? "TRUE" : "FALSE") << endl;

        cout << "Lev. Order: ";
        levelorder();
        cout << "Pre  Order: ";
        preorder();
        cout << "In   Order: ";
        inorder();
        cout << "Post Order: ";
        postorder();
        int small, big;
        getSmallest(small);
        cout << "Smallest = " << small << endl;
        getBiggest(big);
        cout << "Biggest  = " << big << endl;
        for (int i = small; i <= big; i++)
            cout << i << (find(i) ? " found " : " not found.") << endl;

        cout << "______________________________________________" << endl;
    }

    //populates the array buff with the elements of the current object in ascending order.
    void toArray(int buff[]) {
        int currIdx = 0;
        recursiveToArray(root, buff, currIdx);
    }
};

int main()
{
    int treeType = 0;
    int vals[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,16,15,14,13,11,11};
    int valsSize = sizeof(vals) / sizeof(int);
    sort(vals, vals + valsSize);
    int buff[100];

    cout << "Input Tree Type (-1 = TreeLeft, 1 = TreeRight, 0 = TreeAlternating, 2 = Balanced): ";
    cin >> treeType;
    OrderedSet bst1(vals, valsSize, treeType);
    bst1.printInfo();
    bst1.toArray(buff);

    for(int i = 0; i < valsSize; i++) {
        cout << buff[i] << " ";
    }

    return 0;
}
#include <iostream>

using namespace std;

struct TreeNode {
    int value;
    TreeNode *left;
    TreeNode *right;
};

void printInOrder(TreeNode *root) {
    if(root == nullptr) return;
    printInOrder(root->left); 
    cout << root->value << " "; 
    printInOrder(root->right); 
}

int getHeight(TreeNode *root) {
    if(root == nullptr) return 0;
    return 1 + max(getHeight(root->left), getHeight(root->right));
}

int main() {
    TreeNode *t1 = new TreeNode{6, nullptr, nullptr};
    TreeNode *t2 = new TreeNode{9, nullptr, nullptr};
    TreeNode *t3 = new TreeNode{8, nullptr, t2};
    TreeNode *r = new TreeNode{7, t1, t3};
    t2->left = new TreeNode{10};
    t2->left->left = new TreeNode{11};
    t2->left->right = new TreeNode{12};
    t2->left->left->left = new TreeNode{13};

    
    /*
    7
   / \
  6   8
       \
        9
       /
      10
     /  \
    11  12
    /
   13 
    */

    //cout << r->left->value << endl;
    //cout << r->right->value << endl;
    //printInOrder(r);  // should print 6 7 8 9
    cout << getHeight(r);

    return 0;
}
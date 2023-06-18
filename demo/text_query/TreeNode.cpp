#include <iostream>
using std::string;

/**
 * @brief 给下面的类实现默认构造和必要的拷贝构造
 * 
 */

class TreeNode{

public:
    TreeNode()
        : value(string()),count(new int(1)),left(nullptr),right(nullptr) {}
    TreeNode(const TreeNode& tr)
     : value(string(tr.value)), count(tr.count),
        left(tr.left),right(tr.right) { ++*count;}
    TreeNode& operator=(const TreeNode& tr);
    ~TreeNode(){
        if(--*count == 0){
            delete count;
            delete left;
            delete right;
        }
        
    }
private:
    string value;
    int *count;
    TreeNode *left;
    TreeNode *right;
};

class BinStrTree{

public:
    BinStrTree(): root(new TreeNode()){}
    BinStrTree(const BinStrTree &bst)
         : root(new TreeNode(*bst.root)) {}
    BinStrTree& operator=(const BinStrTree &bst);
    ~BinStrTree(){
        delete root;
    }

private:
    TreeNode *root;
};
/**
 * @brief 重载赋值运算符
 * 
 * @param tr 
 * @return TreeNode& 
 */
TreeNode& TreeNode::operator=(const TreeNode& tr){
        ++*tr.count;
        if(--*this->count == 0){
            delete count;
            delete left;
            delete right;
        }
        this->value = tr.value;
        this->count = tr.count;
        this->left = tr.left;
        this->right = tr.right;
        return *this;
}

BinStrTree& BinStrTree::operator=(const BinStrTree &bst){
    auto new_root = new TreeNode(*bst.root);
    delete root;
    this->root = new_root;
    return *this;
}

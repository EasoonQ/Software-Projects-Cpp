#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;
        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    void clear_helper(Node<Key, Value>* current); // clear the bst
    int height_helper(Node<Key, Value>* node) const; // get height of a node
    bool isBalanced_helper(Node<Key, Value>* root) const; // check if bst is balanced

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator()
{
    // TODO
    current_ = NULL;
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return (this->current_ == rhs.current_);
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return (this->current_ != rhs.current_);
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    if (current_ == NULL){
        return *this;
    }

    Node<Key, Value>* temp = current_;

    //if has right child, get the left-most node of the right subtree
    if (current_->getRight() != NULL){
        temp = current_->getRight();
        while (temp->getLeft() != NULL){
            temp = temp->getLeft();
        }
        current_ = temp;
    } else{ //if no right child, walk up and find the first node who is a left child
        current_ = NULL;
        while (temp->getParent() != NULL){
            if ((temp->getParent())->getLeft() == temp){
                current_ = temp->getParent();
                break;
            }
            temp = temp->getParent();
        }
    }
    return *this;
}



/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
    // TODO
    root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    this->clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    if(this->empty()){ //create a root if the tree is empty
        Node<Key, Value>* new_item = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
        root_ = new_item;
    }

    Node<Key, Value>* current = root_;
    while (current != NULL){
        if (current->getKey() < keyValuePair.first){ // search right if keyValuePair's key is larger
            if (current->getRight() == NULL){ // if next node is a leaf, we've found the correct place to insert
                Node<Key, Value>* new_item = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, current);
                current->setRight(new_item);
                return;
            }
            current = current->getRight();
        }
        else if (current->getKey() > keyValuePair.first){ // search left if keyValuePair's key is smaller
            if (current->getLeft() == NULL){ // if next node is a leaf, we've found the correct place to insert
                Node<Key, Value>* new_item = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, current);
                current->setLeft(new_item);
                return;
            }
            current = current->getLeft();
        }
        else if (current->getKey() == keyValuePair.first){ // just update the value if repeated key
            current->setValue(keyValuePair.second);
            return;
        }
    }
}

/**
* A remove method to remove a specific key from a Binary Search Tree.
* The tree may not remain balanced after removal.
*/

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    Node<Key, Value>* current = internalFind(key);
    // do nothing if the node does not exist
    if (current == NULL){
        return;
    }

    if ((current->getLeft() == NULL) && (current->getRight() == NULL)){ // if no children
        if (current == root_){
            root_ = NULL;
            delete root_;
        } else{ // check if current is a left child or right child and do operations respectively
            if (current == (current->getParent())->getLeft()){
                (current->getParent())->setLeft(NULL);
                delete current;
            } else{
                (current->getParent())->setRight(NULL);
                delete current;
            }
        }
    }

    else if (current->getLeft() && current->getRight() == NULL){ // only left child
        Node<Key, Value>* leftChild = current->getLeft();
        if (current == root_){ // if current is root, make left child as root and delete current
            root_ = leftChild;
            leftChild->setParent(NULL);
            delete current;
        }else{ // check if current is a left child or right child and do operations respectively
            if (current == (current->getParent())->getLeft()){
                (current->getParent())->setLeft(leftChild);
            }else{
                (current->getParent())->setRight(leftChild);
            }
            leftChild->setParent(current->getParent());
            delete current;
        }
    }

    else if (current->getLeft() == NULL && current->getRight()){ // only right child
        Node<Key, Value>* rightChild = current->getRight();
        if (current == root_){ // if current is root, make right child as root and delete current
            root_ = rightChild;
            rightChild->setParent(NULL);
            delete current;
        }else{ // check if current is a left child or right child and do operations respectively
            if (current == (current->getParent())->getLeft()){
                (current->getParent())->setLeft(rightChild);
            }else{
                (current->getParent())->setRight(rightChild);
            }
            rightChild->setParent(current->getParent());
            delete current;
        }
    }

    else{ // there are two children
        Node<Key,Value>* pre = predecessor(current);
        nodeSwap(current, pre);
        // current cannot be root_ after swap
        if (current->getLeft() != NULL){ // have 1 left child after swap
            if (current == (current->getParent())->getLeft()){
                (current->getParent())->setLeft(current->getLeft());
            } else{
                (current->getParent())->setRight(current->getLeft());
            }
            current->getLeft()->setParent(current->getParent());
            delete current;
        }
        else if (current->getRight() != NULL){ // have 1 right child after swap
            if (current == (current->getParent())->getLeft()){
                (current->getParent())->setLeft(current->getRight());
            } else{
                (current->getParent())->setRight(current->getRight());
            }
            current->getRight()->setParent(current->getParent());
            delete current;
        } else{ // leaf after swap
            if (current == (current->getParent())->getLeft()){
                current->getParent()->setLeft(NULL);
            }else{
                current->getParent()->setRight(NULL);
            }
            delete current;
        }
    }
}


template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    if (current == NULL){
        return NULL;
    }

    Node<Key, Value>* temp = current;

    //if has left child, get the right-most node of the left subtree
    if (current->getLeft() != NULL){
        temp = current->getLeft();
        while (temp->getRight() != NULL){
            temp = temp->getRight();
        }
        return temp;
    } else{ //if no left child, walk up and find the first node who is a right child
        while (temp->getParent() != NULL){
            if ((temp->getParent())->getRight() == temp){
                return temp->getParent();
            }
            temp = temp->getParent();
        }
        return NULL;
    }
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    clear_helper(root_);
    root_ = NULL;
}

// helper function to clear the tree
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear_helper(Node<Key, Value>* current){
    if (current == NULL){
        return;
    }
    clear_helper(current->getLeft());
    clear_helper(current->getRight());
    delete current;
    current = NULL;
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    if (root_ == NULL){
        return NULL;
    }

    // find left-most node
    Node<Key, Value>* temp = root_;
    while (temp->getLeft() != NULL){
        temp = temp->getLeft();
    }
    return temp;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    Node<Key, Value>* temp = root_;
    while (temp != NULL){
        if (key > temp->getKey()){
            temp = temp->getRight();
        }
        else if (key < temp->getKey()){
            temp = temp->getLeft();
        }
        else if (key == temp->getKey()){
            return temp;
        }
    }
    return temp;
}

// helper function to ger the height of a node
template<class Key, class Value>
int BinarySearchTree<Key, Value>::height_helper(Node<Key, Value>* node) const
{
    if (node == nullptr){
        return 0;
    }
    return 1 + std::max(height_helper(node->getLeft()),height_helper(node->getRight()));
}

// helper function to determine whether a tree is balanced
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::isBalanced_helper(Node<Key, Value>* root) const{
    if(root == nullptr){
        return true;
    }
    //Get the heights of the left and right subtrees
    int lh = height_helper(root->getLeft());
    int rh = height_helper(root->getRight());
    //Determine if this node is balanced! If not ret false!
    if((lh - rh > 1) || (rh - lh > 1)){
        return false;
    }
    //Check if there are subtrees under us are balanced
    return (isBalanced_helper(root->getLeft()) && isBalanced_helper(root->getRight()));
}
/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    return isBalanced_helper(root_);
}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif

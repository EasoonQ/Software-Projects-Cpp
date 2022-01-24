#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"
#include <cmath>

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight () const;
    void setHeight (int height);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int height_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), height_(1)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the height of a AVLNode.
*/
template<class Key, class Value>
int AVLNode<Key, Value>::getHeight() const
{
    return height_;
}

/**
* A setter for the height of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    height_ = height;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void leftRot(AVLNode<Key, Value>* z);
    void rightRot(AVLNode<Key, Value>* z);
    AVLNode<Key, Value>* firstUnbalanced(AVLNode<Key, Value>* node); // the first unbalanced node up from the given node
};

// left rotate on z and update the height below it
template<class Key, class Value>
void AVLTree<Key, Value>::leftRot(AVLNode<Key, Value> *z) {
    AVLNode<Key, Value>* y = z->getRight();
    AVLNode<Key, Value>* y_left = y->getLeft();
    // perform rotation
    y->setLeft(z);
    if (y_left != NULL){
        y_left->setParent(z);
        z->setRight(y_left);
    } else{
        z->setRight(NULL);
    }
    if (z != BinarySearchTree<Key, Value>::root_){
        if (z == z->getParent()->getLeft()){
            z->getParent()->setLeft(y);
        } else{
            z->getParent()->setRight(y);
        }
        y->setParent(z->getParent());
    } else{ // z is originally the root of the tree
        y->setParent(NULL);
        BinarySearchTree<Key, Value>::root_ = y;
    }
    z->setParent(y);

    // update height after rotating
    int lh = 0;
    int rh = 0;
    if (z->getLeft() != NULL){
        lh = z->getLeft()->getHeight();
    }
    if (z->getRight() != NULL){
        rh = z->getRight()->getHeight();
    }
    z->setHeight(std::max(lh+1, rh+1));

    if (y->getRight() != NULL){
        y->setHeight(std::max(y->getLeft()->getHeight() + 1, y->getRight()->getHeight() + 1));
    } else{
        y->setHeight(y->getLeft()->getHeight() + 1);
    }
}


// right totate on z and update the height below it
template<class Key, class Value>
void AVLTree<Key, Value>::rightRot(AVLNode<Key, Value> *z) {
    AVLNode<Key, Value>* y = z->getLeft();
    AVLNode<Key, Value>* y_right = y->getRight();
    // perform rotation
    y->setRight(z);
    if (y_right != NULL){
        y_right->setParent(z);
        z->setLeft(y_right);
    } else{
        z->setLeft(NULL);
    }
    if (z != BinarySearchTree<Key, Value>::root_){
        if (z == z->getParent()->getLeft()){
            z->getParent()->setLeft(y);
        } else{
            z->getParent()->setRight(y);
        }
        y->setParent(z->getParent());
    } else{ // z is originally the root of the tree
        y->setParent(NULL);
        BinarySearchTree<Key, Value>::root_ = y;
    }
    z->setParent(y);

    // update height after rotating
    int lh = 0;
    int rh = 0;
    if (z->getLeft() != NULL){
        lh = z->getLeft()->getHeight();
    }
    if (z->getRight() != NULL){
        rh = z->getRight()->getHeight();
    }
    z->setHeight(std::max(lh+1, rh+1));

    if (y->getLeft() != NULL){
        y->setHeight(std::max(y->getLeft()->getHeight() + 1, y->getRight()->getHeight() + 1));
    } else{
        y->setHeight(y->getRight()->getHeight() + 1);
    }
}

// this function find the first unbalanced node up from a given node
// and update the height of each node along the way
template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::firstUnbalanced(AVLNode<Key, Value> *node) {
    AVLNode<Key, Value>* temp = node;
    while (temp != NULL){
        int lh = 0;
        int rh = 0;
        if (temp->getLeft()){
            lh = temp->getLeft()->getHeight();
        }
        if (temp->getRight()){
            rh = temp->getRight()->getHeight();
        }
        if (temp->getHeight() != std::max(lh+1, rh+1)){
            temp->setHeight(std::max(lh+1, rh+1)); // update the height along the way
        }
        if (abs(lh-rh) > 1){
            return temp;
        }
        temp = temp->getParent();
    }
    return temp; // return NULL if all the nodes are already balanced
}

template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    // perform the regular bst insert
    if(BinarySearchTree<Key, Value>::empty()){ //create a root
        AVLNode<Key, Value>* new_node = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
        new_node->setHeight(1);
        BinarySearchTree<Key, Value>::root_ = new_node;
        return;
    }

    AVLNode<Key, Value>* current = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::root_);
    while (current != NULL){
        if (current->getKey() < new_item.first){
            if (current->getRight() == NULL){
                AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, current);
                current->setRight(newNode);
                newNode->setHeight(1);
                break;
            }
            current = current->getRight();
        }
        else if (current->getKey() > new_item.first){
            if (current->getLeft() == NULL){
                AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, current);
                current->setLeft(newNode);
                newNode->setHeight(1);
                break;
            }
            current = current->getLeft();
        }
        else if (current->getKey() == new_item.first){
            current->setValue(new_item.second);
            return;
        }
    }

    // find the first unbalanced node
    AVLNode<Key, Value>* unbalanceNode = firstUnbalanced(current);
    if (unbalanceNode == NULL){
        return;
    }
    AVLNode<Key, Value>* lower1 = NULL;
    int state1 = -1;
    int state2 = -1;
    // 00 for left-left, 01 for left-right, 11 for right-right, 10 for right-left
    int lh1 = 0;
    int rh1 = 0;
    if (unbalanceNode->getLeft()){
        lh1 = unbalanceNode->getLeft()->getHeight();
    }
    if (unbalanceNode->getRight()){
        rh1 = unbalanceNode->getRight()->getHeight();
    }
    // no need to check NULL cuz it must have at least 1 child
    // also, ties are impossible
    if (lh1 > rh1){
        lower1 = unbalanceNode->getLeft();
        state1 = 0;
    } else{
        lower1 = unbalanceNode->getRight();
        state1 = 1;
    }
    int lh2 = 0;
    int rh2 = 0;
    if (lower1->getLeft()){
        lh2 = lower1->getLeft()->getHeight();
    }
    if (lower1->getRight()){
        rh2 = lower1->getRight()->getHeight();
    }
    // no need to check NULL cuz it must have at least 1 child
    // also, ties are impossible
    if (lh2 > rh2){
        state2 = 0;
    } else{
        state2 = 1;
    }
    if (state1 == 0 && state2 == 0){ // left-left
        rightRot(unbalanceNode);
    }
    else if (state1 == 1 && state2 == 1){ // right-right
        leftRot(unbalanceNode);
    }
    else if (state1 == 0 && state2 == 1){ // left-right
        leftRot(lower1);
        rightRot(unbalanceNode);
    } else{ // right-left
        rightRot(lower1);
        leftRot(unbalanceNode);
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    // perform normal bst remove
    AVLNode<Key, Value>* current = static_cast<AVLNode<Key,Value>*>(BinarySearchTree<Key,Value>::internalFind(key));
    // do nothing if the node does not exist
    if (current == NULL){
        return;
    }

    AVLNode<Key,Value>* parent = current->getParent();
    if ((current->getLeft() == NULL) && (current->getRight() == NULL)){ // if no children
        if (current == BinarySearchTree<Key, Value>::root_){
            BinarySearchTree<Key, Value>::root_ = NULL;
            delete BinarySearchTree<Key, Value>::root_;
            return;
        } else{
            if (current == parent->getLeft()){
                parent->setLeft(NULL);
                delete current;
            } else{
                parent->setRight(NULL);
                delete current;
            }
        }
    }
    else if (current->getLeft() && current->getRight() == NULL){ // only left child
        AVLNode<Key, Value>* leftChild = current->getLeft();
        if (current == BinarySearchTree<Key,Value>::root_){
            BinarySearchTree<Key, Value>::root_ = leftChild;
            leftChild->setParent(NULL);
            delete current;
            return;
        }else{
            if (current == parent->getLeft()){
                parent->setLeft(leftChild);
            }else{
                parent->setRight(leftChild);
            }
            leftChild->setParent(parent);
            delete current;
        }
    }

    else if (current->getLeft() == NULL && current->getRight()){ // only right child
        AVLNode<Key, Value>* rightChild = current->getRight();
        if (current == BinarySearchTree<Key, Value>::root_){
            BinarySearchTree<Key, Value>::root_ = rightChild;
            rightChild->setParent(NULL);
            delete current;
            return;
        }else{
            if (current == parent->getLeft()){
                parent->setLeft(rightChild);
            }else{
                parent->setRight(rightChild);
            }
            rightChild->setParent(parent);
            delete current;
        }
    }

    else{ // there are two children
        AVLNode<Key,Value>* pre = static_cast<AVLNode<Key,Value>*>(BinarySearchTree<Key, Value>::predecessor(current));
        nodeSwap(current, pre);
        parent = current->getParent();
        //after swap, can have at most 1 child
        if (current->getLeft() != NULL){ // have 1 left child after swap
            if (current == parent->getLeft()){
                parent->setLeft(current->getLeft());
            } else{
                parent->setRight(current->getLeft());
            }
            current->getLeft()->setParent(parent);
            delete current;
        }
        else if (current->getRight() != NULL){ // have 1 right child after swap
            if (current == parent->getLeft()){
                parent->setLeft(current->getRight());
            } else{
                parent->setRight(current->getRight());
            }
            current->getRight()->setParent(current->getParent());
            delete current;
        } else{ // leaf after swap
            if (current == parent->getLeft()){
                parent->setLeft(NULL);
            }else{
                parent->setRight(NULL);
            }
            delete current;
        }
    }

    // find the first unbalanced node
    AVLNode<Key, Value>* unbalanceNode = firstUnbalanced(parent);
    while (unbalanceNode != NULL) {
        AVLNode<Key, Value> *lower1 = NULL;
        int state1 = -1;
        int state2 = -1;
        // 00 for left-left, 01 for left-right, 11 for right-right, 10 for right-left
        int lh1 = 0;
        int rh1 = 0;
        if (unbalanceNode->getLeft()) {
            lh1 = unbalanceNode->getLeft()->getHeight();
        }
        if (unbalanceNode->getRight()) {
            rh1 = unbalanceNode->getRight()->getHeight();
        }
        // no need to check NULL cuz it must have at least 1 child
        // also, ties are impossible
        if (lh1 > rh1){
            lower1 = unbalanceNode->getLeft();
            state1 = 0;
        } else{
            lower1 = unbalanceNode->getRight();
            state1 = 1;
        }
        int lh2 = 0;
        int rh2 = 0;
        if (lower1->getLeft()){
            lh2 = lower1->getLeft()->getHeight();
        }
        if (lower1->getRight()){
            rh2 = lower1->getRight()->getHeight();
        }
        // no need to check NULL cuz it must have at least 1 child
        // break ties in preference of 1 rotation
        if (lh2 > rh2) {
            state2 = 0;
        } else if (lh2 < rh2) {
            state2 = 1;
        } else {
            if (state1 == 0) {
                state2 = 0;
            } else {
                state2 = 1;
            }
        }
        if (state1 == 0 && state2 == 0) { // left-left
            rightRot(unbalanceNode);
        } else if (state1 == 1 && state2 == 1) { // right-right
            leftRot(unbalanceNode);
        } else if (state1 == 0 && state2 == 1) { // left-right
            leftRot(lower1);
            rightRot(unbalanceNode);
        } else { // right-left
            rightRot(lower1);
            leftRot(unbalanceNode);
        }
        unbalanceNode = firstUnbalanced(unbalanceNode);
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int tempH = n1->getHeight();
    n1->setHeight(n2->getHeight());
    n2->setHeight(tempH);
}


#endif

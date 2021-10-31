//
// Created by Eason Qin on 10/10/21.
//

#ifndef HW3_MINHEAP_H
#define HW3_MINHEAP_H

#include "iostream"
#include <vector>

template<class T>
class MinHeap {
public:
    MinHeap(int d);
    /* Constructor that builds a d-ary Min Heap
       This should work for any d >= 2,
       but doesn't have to do anything for smaller d.*/

    ~MinHeap();

    void add(T item, int priority);
    /* adds the item to the heap, with the given priority. */

    const T& peek() const;
    /* returns the element with smallest priority.
       Break ties however you wish.
       Throws an exception if the heap is empty. */

    void remove();
    /* removes the element with smallest priority.
       Break ties however you wish.
       Throws an exception if the heap is empty. */

    bool isEmpty();
    /* returns true iff there are no elements on the heap. */

private:
    std::vector<T> myItem;
    std::vector<int> myPriority;
    int ary;
    int findSmallestChild(int i);  // given position i, find its smallest child's position
    void bubbleUp(int i);
    void trickledown(int i);
};

template<class T>
MinHeap<T>::MinHeap(int d) {
    if (d >= 2) {
        ary = d;
        myItem.clear();
        myPriority.clear();
    }
}

template<class T>
MinHeap<T>::~MinHeap() {}

template<class T>
int MinHeap<T>::findSmallestChild(int i) {
    int small = 1;
    for (int k = 2; (ary * i + k) < (int)myItem.size() && k <= ary; k++) {
        if (myPriority[ary * i + k] < myPriority[ary * i + small]) {
            small = k;
        }
        // if there's a tie, find the one with the smallest item (with < operation)
        else if (
                myPriority[ary * i + k] == myPriority[ary * i + small]
                && myItem[ary * i + k] < myItem[ary * i + small]) {
            small = k;
        }
    }
    return (ary * i + small);
}

template<class T>
void MinHeap<T>::bubbleUp(int i) {
    if (i > 0) {
        int a = (i - 1) / ary;
        if (myPriority[i] < myPriority[a]) {
            std::swap(myItem[i], myItem[a]);
            std::swap(myPriority[i], myPriority[a]);
            bubbleUp(a);
        }
        // if there's a tie, bubble up if myItem[i] is a smaller item
        if (myPriority[i] == myPriority[a]) {
            if ((myItem[i] < myItem[a])) {
                std::swap(myItem[i], myItem[a]);
                std::swap(myPriority[i], myPriority[a]);
                bubbleUp(a);
            }
        }
    }
}

template<class T>
void MinHeap<T>::trickledown(int i) {
    if ((ary * i + 1) < (int)myItem.size()) {
        int a = findSmallestChild(i);
        if (myPriority[i] > myPriority[a]) {
            std::swap(myItem[i], myItem[a]);
            std::swap(myPriority[i], myPriority[a]);
            trickledown(a);
        }
        // if there's a tie, trickle if myItem[i] is a bigger item
        else if (myPriority[i] == myPriority[a]) {
            if (!(myItem[i] < myItem[a])) {
                std::swap(myItem[i], myItem[a]);
                std::swap(myPriority[i], myPriority[a]);
                trickledown(a);
            }
        }
    }
}

template<class T>
const T& MinHeap<T>::peek() const {
    if (myItem.empty()) {
        throw std::invalid_argument("Nothing to peek");
    }
    return myItem[0];
}

template<class T>
bool MinHeap<T>::isEmpty() {
    return (myItem.size() == 0);
}

template<class T>
void MinHeap<T>::add(T item, int priority) {
    // push the item to the back and then bubble up
    myItem.push_back(item);
    myPriority.push_back(priority);
    bubbleUp(myItem.size() - 1);
}

template<class T>
void MinHeap<T>::remove() {
    if (myItem.empty()) {
        throw std::invalid_argument("Nothing to remove");
    }
    // swap the top and the back, remove the back, and then trickle down the head
    std::swap(myItem[0], myItem[myItem.size() - 1]);
    std::swap(myPriority[0], myPriority[myPriority.size() - 1]);
    myItem.pop_back();
    myPriority.pop_back();
    trickledown(0);
}

#endif  // HW3_MINHEAP_H

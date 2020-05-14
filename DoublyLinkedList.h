//
// Created by Guy Steinberg on 5/14/20.
//

#ifndef WET1_LINKEDLIST_H
#define WET1_LINKEDLIST_H

#include "Node.h"

template <class T>
class DoublyLinkedList {
private:
    BasicNode<T>* head_;
    BasicNode<T>* tail_;

public:
    DoublyLinkedList() : head_(NULL), tail_(NULL) {}
    ~DoublyLinkedList();

    //class methods
    BasicNode<T>* getHead() const { return head_; }
    BasicNode<T>* getTail() const { return tail_; }

    bool InsertNodeAfter(BasicNode<T>* prev_node, const T& value);
    bool InsertNodeHead(const T& value);
    void insertNodeTail(BasicNode<T>* tail);
};

template <class T>
bool DoublyLinkedList<T>::InsertNodeHead(const T& value) {
    BasicNode<T>* new_node = new (std::nothrow) BasicNode<T>(value);

    if(!new_node)
        return true; // Out of memory

    if(!head_)
        head_ = new_node;
    else {
        new_node->setPrev(tail_);
        new_node->setNext(head_);
        head_->setPrev(new_node);
    }
    return false;
}

template <class T>
bool DoublyLinkedList<T>::InsertNodeAfter(BasicNode<T> *prev_node, const T &value) {
    BasicNode<T>* new_node = new (std::nothrow) BasicNode<T>(value);

    if(!new_node)
        return true; // Out of memory

    new_node->setNext(prev_node->getNext());
    new_node->setPrev(prev_node);
    prev_node->setNext(new_node);
    return false;
}


#endif //WET1_LINKEDLIST_H

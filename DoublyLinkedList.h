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

    void DeleteList(BasicNode<T>* node);
public:
    DoublyLinkedList() : head_(NULL), tail_(NULL) {}
    ~DoublyLinkedList();

    //class methods
    BasicNode<T>* getHead() const { return head_; }
    BasicNode<T>* getTail() const { return tail_; }
    void RemoveNode(BasicNode<T>* node);
    bool InsertNodeBetween(BasicNode<T>* prev_node,BasicNode<T> *next_node, const T& value);
    bool InsertNodeHead(const T& value);
    bool InsertNodeTail(const T& value);


};
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList<T>(){
    if(head_) {
        DeleteList(head_);
    }
}
template <class T>
void DoublyLinkedList<T>::RemoveNode(BasicNode<T>* node){
    if(node ==NULL)
        return;
    if(node->getNext() == NULL){ //last in list
        if(node->getPrev() != NULL){//not first in list
            node->getPrev()->setNext(NULL);
            tail_= node->getPrev();
        }else{//only node in list
            tail_= NULL;
            head_ = NULL;
        }
    } else {//not last in list
        if(node->getPrev() != NULL){ //not first in list
            node->getPrev()->setNext(node->getNext());
            node->getNext()->setPrev(node->getPrev());
        }else{//first in list
            node->getNext()->setPrev(NULL);
            head_= node->getNext();
        }
    }
    delete(node);
}
template <class T>
void DoublyLinkedList<T>::DeleteList(BasicNode<T>* node){
    if(node != NULL){
        DeleteList(node->getNext());
        delete(node);
    }
}

template <class T>
bool DoublyLinkedList<T>::InsertNodeHead(const T& value) {
    BasicNode<T>* new_node = new (std::nothrow) BasicNode<T>(value);

    if(!new_node)
        return true; // Out of memory

    if(!head_) { //if there is no head (empty list)

        head_ = new_node;
        tail_ = new_node;
    }
    else {
        new_node->setPrev(NULL);
        new_node->setNext(head_);
        head_->setPrev(new_node);
        head_ = new_node;
    }
    return false;
}
template <class T>
bool DoublyLinkedList<T>::InsertNodeTail(const T& value){
    BasicNode<T>* new_node = new (std::nothrow) BasicNode<T>(value);
    if(!new_node)
        return true; // Out of memory

    tail_->setNext(new_node);
    new_node->setPrev(tail_);
    new_node->setNext(NULL);
    tail_ = new_node;
    return false;

}

/***
 *
 * @tparam T Data Type
 * @param prev_node - node to be before new node (if NULL then new node will become the head)
 * @param next_node - node to be after new node (if NULL then new node will become the tail)
 * @param value - value to put in new node
 * @return - true if memory error, false if successful
 */
template <class T>
bool DoublyLinkedList<T>::InsertNodeBetween(BasicNode<T> *prev_node, BasicNode<T> *next_node, const T& value) {
    if(prev_node == NULL) {
        InsertNodeHead(value);
        return false;
    }
    if(next_node == NULL) {
        InsertNodeTail(value);
        return false;
    }
    BasicNode<T>* new_node = new (std::nothrow) BasicNode<T>(value);

    if(!new_node)
        return true; // Out of memory


    next_node->setPrev(new_node);
    new_node->setNext(next_node);
    new_node->setPrev(prev_node);
    prev_node->setNext(new_node);
    return false;
}

#endif //WET1_LINKEDLIST_H

//
// Created by Guy Steinberg on 5/14/20.
//

#ifndef WET1_NODE_H
#define WET1_NODE_H

#include <iostream>

template <class T>
class BasicNode {
private:
    T data_;
    BasicNode* prev_;
    BasicNode* next_;
public:
    //constructor
    BasicNode(const T& data_value) : data_(data_value), prev_(NULL), next_(NULL) {}
    const T& getData() const {return data_;}

    //specific function for our use in organizing AVL trees based on int numbers
    const int getDataToCompare() const {return data_.getDataToCompare();}

    void setPrev(BasicNode* prev) {prev_ = prev;}
    void setNext(BasicNode* next) {next_ = next;}
    BasicNode* getPrev() const {return prev_; }
    BasicNode* getNext() const {return next_; }

    ~BasicNode() {
        data_.DeleteData();
    }
};


template <class T>
class AVLNode {
private:
    T data_;
    AVLNode* left_;
    AVLNode* right_;
    AVLNode* parent_;
public:
    //Constructor with value
    AVLNode(const T& data_value) : data_(data_value), left_(NULL), right_(NULL), parent_(NULL) {}
    //class methods
    const T&  getData() const { return data_; }

    //specific function for our use in organizing AVL trees based on int numbers
    const int getDataToCompare() const {return data_.getDataToCompare();}

    void      setLeft(AVLNode* left) { left_ = left; }
    void      setRight(AVLNode* right) { right_ = right; }
    void      setParent(AVLNode* parent) { parent_ = parent; }
    void      setData(T data) {data_ = data;}

    AVLNode*  getLeft() const { return left_; }
    AVLNode*  getRight() const { return right_; }
    AVLNode*  getParent() const { return parent_; }

    ~AVLNode() {
       data_.DeleteData();
    }
};
#endif //WET1_NODE_H

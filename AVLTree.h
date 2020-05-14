//
// Created by Guy Steinberg on 5/14/20.
//

#ifndef WET1_TREE_H
#define WET1_TREE_H

#include "Node.h"

template <class T>
class AVLTree {
private:
    AVLNode<T>* root_;
    AVLNode<T>* min_;


public:
    AVLTree() : root_(NULL), min_(NULL){}
    //AVLTree(AVLNode<T>* root) : root_(root), min_(root) {}
    //TODO deconstructor
    ~AVLTree();

    //class methods

    bool Insert(const T& value);

    void InsertNode(AVLNode<T>* root, AVLNode<T>* ins);
    void RemoveNode(AVLNode<T>* node);
    void DeleteTree(AVLNode<T>* root);
    AVLNode<T>* getMinNode();

    AVLNode<T>* getRoot() const { return root_; }

    AVLNode<T>* Find(AVLNode<T>* root, const int data) const;

    int  Height(AVLNode<T>* root) const;
    int  BalanceFactor(AVLNode<T>* root) const;

    void RotateLeft (AVLNode<T>* root);
    void RotateRight(AVLNode<T>* root);
};
template <class T>
AVLTree<T>::~AVLTree() {
    if( root_ ) {
        DeleteNode(root_);
    }
}

template <class T>
void AVLTree<T>::DeleteTree(AVLNode<T>* root) {
    if( root ) {
        DeleteTree( root->getLeft() );
        DeleteTree( root->getRight() );
        delete root;
    }
}

template <class T>
AVLNode<T>* AVLTree<T>::getMinNode(){
    return min_;
}

//find the correct spot in AVL tree based on int value (used to sort the tree)
//O(log n) since AVL is Binary Search Tree
template <class T>
AVLNode<T>* AVLTree<T>::Find(AVLNode<T>* root, const int data) const {
    if( root ) {
        if( root->getDataToCompare() == data )
            return root; // Found
        else if( data < root->getDataToCompare())
            return Find( root->getLeft(), data );
        else
            return Find( root->getRight(), data );
    }

    return NULL;
}

template <class T>
bool AVLTree<T>::Insert(const T& value) {
    AVLNode<T>* new_node = new (std::nothrow) AVLNode<T>(value);

    if( !new_node )
        return true; // Out of memory

    if(value.getDataToCompare() > min_->getDataToCompare()) {
        min_ = new_node;
    }
    if( !root_ )
        root_ = new_node;
    else
        InsertNode(root_, new_node);

    return false;
}

template <class T>
void AVLTree<T>::InsertNode(AVLNode<T>* root, AVLNode<T>* newNode) {
    //inserting a new node to a Binary Search Tree
    if (newNode->getDataToCompare() <= root->getDataToCompare()) {
        if (root->getLeft()) // keep searching on left side of tree
            InsertNode(root->getLeft(), newNode);
        else { // Found the right spot
            root->setLeft(newNode);
            newNode->setParent(root);
        }
    } else {
        if (root->getRight()) // keep searching on right side of tree
            InsertNode(root->getRight(), newNode);
        else {// Found the right spot
            root->setRight(newNode);
            newNode->setParent(root);
        }
    }

    // AVL balancing algorithm
    int balance = BalanceFactor(root);
    if( balance > 1 ) { // left tree unbalanced
        if( BalanceFactor( root->getLeft() ) < 0 ) // right child of left tree
            RotateLeft( root->getLeft() ); // double rotation
        RotateRight(root);
    }
    else if( balance < -1 ) { // right tree unbalanced
        if( BalanceFactor( root->getRight() ) > 0 ) // left child of right tree
            RotateRight( root->getRight() );
        RotateLeft(root);
    }
}

//TODO implement removeNode with avl balancing algorithm
template <class T>
void AVLTree<T>::RemoveNode(AVLNode<T> *node) {

}

template <class T>
int AVLTree<T>::Height(AVLNode<T>* root) const {
    int height = 0;
    if( root ) {
        int left  = Height(root->getLeft());
        int right = Height(root->getRight());
        height = 1 + ((left > right) ? left : right) ;
    }
    return height;
}

template <class T>
int  AVLTree<T>::BalanceFactor(AVLNode<T>* root) const {
    int balance = 0;
    if( root ) {
        balance = Height(root->getLeft()) - Height(root->getRight());
    }
    return balance;
}

template <class T>
void AVLTree<T>::RotateLeft (AVLNode<T>* root) {
    AVLNode<T>* newroot = root->getRight();
    root->setRight(newroot->getLeft());
    newroot->setLeft(root);

    if( root->getParent() == NULL ) {
        root_ = newroot;
        newroot->setParent(NULL);
    }
    else {
        if( root->getParent()->getLeft() == root ) {
            root->getParent()->setLeft(newroot);
        }
        else {
            root->getParent()->setRight(newroot);
        }
        newroot->setParent(root->getParent());
    }
    root->setParent(newroot);
}

template <class T>
void AVLTree<T>::RotateRight(AVLNode<T>* root) {
    // Rotate node
    AVLNode<T>* newroot = root->getLeft();
    root->setLeft(newroot->getRight());
    newroot->setRight(root);

    // Adjust tree
    if( root->getParent() == NULL ) {
        root_ = newroot;
        newroot->setParent(NULL);
    }
    else {
        if( root->getParent()->getLeft() == root ) {
            root->getParent()->setLeft(newroot);
        }
        else {
            root->getParent()->setRight(newroot);
        }
        newroot->setParent(root->getParent());
    }

    root->setParent(newroot);
}
#endif //WET1_TREE_H
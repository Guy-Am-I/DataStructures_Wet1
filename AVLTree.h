//
// Created by Guy Steinberg on 5/14/20.
//

#ifndef WET1_TREE_H
#define WET1_TREE_H

#include "Node.h"
#include <iostream>
#include <string>
using namespace std;
//TODO erase helper "trunk" for printing trees
struct Trunk
{
    Trunk *prev;
    string str;

    Trunk(Trunk *prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

template <class T>
class AVLTree {
private:
    AVLNode<T>* root_;
    AVLNode<T>* min_;

    void DeleteTree(AVLNode<T>* node);
public:
    AVLTree() : root_(NULL), min_(NULL){}
    ~AVLTree();

    void printTree(AVLNode<T> *root, Trunk *prev, bool isLeft);

    //class methods
    bool Insert(const T& value);

    void InsertNode(AVLNode<T>* root, AVLNode<T>* ins);
    AVLNode<T>* RemoveNode(AVLNode<T>* root, AVLNode<T>* node);
    AVLNode<T>* innerRemoveNode(AVLNode<T>* root, AVLNode<T>* node);
    AVLNode<T>* getMinNode();

    AVLNode<T>* getRoot() const { return root_; }

    AVLNode<T>* Find(AVLNode<T>* root, const int data) const;

    int  Height(AVLNode<T>* root) const;
    int  BalanceFactor(AVLNode<T>* root) const;

    void RotateLeft (AVLNode<T>* root);
    void RotateRight(AVLNode<T>* root);

    AVLNode<T>* SubTreeMinNode(AVLNode<T> *node);

};

template <class T>
AVLTree<T>::~AVLTree() {
    if(root_) {
        DeleteTree(root_);
    }
}
template <class T>
void AVLTree<T>::DeleteTree(AVLNode<T>* node){
    if(node != NULL){
        std::cout << "here" << std::endl;
        DeleteTree(node->getRight());
        DeleteTree(node->getLeft());
        delete(node);
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
            return Find(root->getLeft(), data);
        else
            return Find(root->getRight(), data);
    }

    return NULL;
}

template <class T>
bool AVLTree<T>::Insert(const T& value) {
    AVLNode<T>* new_node = new (std::nothrow) AVLNode<T>(value);

    if( !new_node )
        return true; // Out of memory


    if( !root_ ) {
        root_ = new_node;
        min_ = root_;
    }
    else {
        if(value.getDataToCompare() < min_->getDataToCompare()) {
            min_ = new_node;
        }
        InsertNode(root_, new_node);
    }

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



template <class T>
AVLNode<T>* AVLTree<T>::innerRemoveNode(AVLNode<T> *root, AVLNode<T>* node) {

    // Find the node and delete it
    if (root == NULL)
        return root;
    if (node->getDataToCompare() < root->getDataToCompare())
        root->setLeft(RemoveNode(root->getLeft(), node));
    else if (node->getDataToCompare() > root->getDataToCompare())
        root->setRight(RemoveNode(root->getRight(), node));
    else {
        if ((root->getLeft() == NULL) ||
            (root->getRight() == NULL)) {
            AVLNode<T> *temp = root->getLeft() ? root->getLeft() : root->getRight();
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;

            delete(temp); //deleting the node

        } else {

            AVLNode<T> *temp = SubTreeMinNode(root->getRight());

            root->setData(temp->getData());

            root->setRight(RemoveNode(root->getRight(),temp));
        }
    }
    if (root == NULL) {
        return root;
    }


    // AVL balancing algorithm
    int balance = BalanceFactor(root);
    if (balance > 1) { // left tree unbalanced
        if (BalanceFactor(root->getLeft()) < 0) // right child of left tree
            RotateLeft(root->getLeft()); // double rotation
        RotateRight(root);
    } else if (balance < -1) { // right tree unbalanced
        if (BalanceFactor(root->getRight()) > 0) // left child of right tree
            RotateRight(root->getRight());
        RotateLeft(root);
    }
    return root;
}
template <class T>
AVLNode<T>* AVLTree<T>::RemoveNode(AVLNode<T> *root, AVLNode<T>* node) {
    AVLNode<T>* new_root = innerRemoveNode(root, node);
    if(new_root == NULL) {
        root_ = NULL;
        min_ = NULL;
    }
    return new_root;
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
template <class T>
AVLNode<T>* AVLTree<T>::SubTreeMinNode(AVLNode<T> *node) {
    AVLNode<T> *current = node;
    while (current->getLeft() != NULL)
        current = current->getLeft();
    return current;
}

//TODO delete code when done
//////ONLINE CODE TO PRINT TREE IN UNDERSTANDABLE WAY////////


// Helper function to print branches of the binary tree
void showTrunks(Trunk *p)
{
    if (p == nullptr)
        return;

    showTrunks(p->prev);

    cout << p->str;
}

// Recursive function to print binary tree
// It uses inorder traversal
template <class T>
void AVLTree<T>::printTree(AVLNode<T> *root, Trunk *prev, bool isLeft)
{
    if (root == nullptr)
        return;

    string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);

    printTree(root->getLeft(), trunk, true);

    if (!prev)
        trunk->str = "---";
    else if (isLeft)
    {
        trunk->str = ".---";
        prev_str = "   |";
    }
    else
    {
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << root->getDataToCompare() << endl;

    if (prev)
        prev->str = prev_str;
    trunk->str = "   |";

    printTree(root->getRight(), trunk, false);
}

#endif //WET1_TREE_H
//
// Created by Jason Ketterer on 4/21/22.
//

#include <iostream>
#include <algorithm>
#include <math.h>
#include "queue.h"
#include "list.h"
#include "bst.h"

template <typename T>
BST<T>::~BST() {
    if(root_ != nullptr) {
        Clear(root_);
        root_ = nullptr;
    }
}

template <typename T>
void BST<T>::Insert(const T & t) {
    RInsert(root_, t);
}

template <typename T>
void BST<T>::Remove(const T & t) {
    RRemove(root_, t);
}

template<typename T>
bool BST<T>::Contains(const T &t) const {
    return RContains(root_, t);
}

template<typename T>
T & BST<T>::Get(const T &t) {
    return RGet(root_, t);
}

template <typename T>
void BST<T>::Clear() {
    Clear(root_);
}

template <typename T>
size_t BST<T>::Height() const {
    if(root_ == nullptr) return 0;
    return RHeight(root_) - 1;
    // we subtract 1 because RHeight counts the root but root is at height 0
}

template <typename T>
size_t BST<T>::Size() const {
    if(root_ == nullptr) return 0;
    return RSize(root_);
}

template <typename T>
void BST<T>::PreOrder() const {
    std::cout << "Preorder traversal: \n";
    RPreOrder(root_);
}

template <typename T>
void BST<T>::InOrder() const {
    std::cout << "Inorder traversal: \n";
    RInOrder(root_);
}

template <typename T>
void BST<T>::PostOrder() const {
    std::cout << "Postorder traversal: \n";
    RPostOrder(root_);
}

template <typename T>
void BST<T>::LevelOrder() const {
    std::cout << "Levelorder traversal: \n";
    if(root_ == nullptr) return;
    Queue<Node *> q;
    q.Push(root_);
    Node * front;
    while(!q.Empty()) {
        front = q.Front();
        if(front != nullptr) {
            q.Push(front->lchild_);
            q.Push(front->rchild_);
            std::cout << front->val_ << ' ';
        }
        q.Pop();
    }
}

template <typename T>
void BST<T>::printHTree() const {
    RPrintHTree(root_, 0);
}

template <typename T>
void BST<T>::printVTree() const {
    List<Node *> treeLevel;
    treeLevel.PushFront(root_);
    List<Node *> temp;
    int counter = 0;
    int height = Height();
    double numOfNodes = pow(2, height+1) - 1;
    while(counter <= height) {
        Node * removed = treeLevel.Front();
        treeLevel.PopFront();
        if(temp.Empty())
            printSpace(numOfNodes / pow(2, counter+1), removed);
        else
            printSpace(numOfNodes / pow(2, counter), removed);
        if(removed == nullptr) {
            temp.PushBack(nullptr);
            temp.PushBack(nullptr);
        }
        else {
            temp.PushBack(removed->lchild_);
            temp.PushBack(removed->rchild_);
        }
        if(treeLevel.Empty()) {
            std::cout << "\n";
            std::cout << "\n";
            treeLevel = temp;
            temp.Clear();
            ++counter;
        }
    }
}

/*************************************
 * Protected methods
 *************************************/

template <typename T>
typename BST<T>::Node * BST<T>::findMin(Node * n) const {
    if(n == nullptr)
        return nullptr;
    while(n->lchild_ != nullptr) {
        n = n->lchild_;
    }
    return n;
}

template <typename T>
typename BST<T>::Node * BST<T>::findMax(Node * n) const {
    if(n == nullptr)
        return nullptr;
    while(n->rchild_ != nullptr) {
        n = n->rchild_;
    }
    return n;
}

template <typename T>
void BST<T>::printSpace(double n, Node * removed) const {
    for(; n > 0; --n)
        std::cout << '\t';
    if(removed == nullptr)
        std::cout << ' ';
    else
        std::cout << removed->val_;
}

template <typename T>
size_t BST<T>::RHeight(Node * n) const {
    if(n == nullptr)
        return 0;
    return std::max(RHeight(n->lchild_), RHeight(n->rchild_)) + 1;
}

template <typename T>
size_t BST<T>::RSize(Node * n) const {
    if(n == nullptr)
        return 0;
    size_t lsize = 0, rsize = 0;
    if(n->lchild_)
        lsize = RSize(n->lchild_);
    if(n->rchild_)
        rsize = RSize(n->rchild_);
    return 1 + lsize + rsize;  // node counts itself and then adds the number of nodes in its left/right subtrees
}

template <typename T>
void BST<T>::RPrintHTree(Node * n, int space) const {
    int COUNT = 5;
    // Base case
    if (n == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    RPrintTree(n->rchild_, space);

    // Print current node after space
    // count
    std::cout<<'\n';
    for (int i = COUNT; i < space; i++)
        std::cout<<" ";
    std::cout<<n->val_<<"\n";

    // Process left child
    RPrintTree(n->lchild_, space);
}

template <typename T>
typename BST<T>::Node * BST<T>::CreateNode(const T & t) {
    Node * newNode = new(std::nothrow) Node(t);
    if(newNode == nullptr) {
        std::cerr << "**Unable to allocate memory for new Node\n";
        return nullptr;
    }
    return newNode;
}

template <typename T>
void BST<T>::RInsert(Node * & n, const T & t) {
    if(n == nullptr) {
        Node * newNode = CreateNode(t);
        n = newNode;
        return;
    }
    if(t < n->val_)
        RInsert(n->lchild_, t);
    else if(t > n->val_)
        RInsert(n->rchild_, t);
    else // value already exists in the tree, do nothing
        return;
}

template<typename T>
void BST<T>::RRemove(BST::Node *&n, const T &t) {
    if(n == nullptr) // t not found; do nothing
        return;
    if(t < n->val_)
        RRemove(n->lchild_, t);
    else if(t > n->val_)
        RRemove(n->rchild_, t);
    else { // we found the node to remove
        if(n->lchild_ != nullptr && n->rchild_ != nullptr) {
            // node to remove has 2 children
            // need to find largest value in left subtree or smallest value
            // in right subtree, copy it to the node we want to delete and then
            // delete the node we just copied (to prevent a duplicate)
            n->val_ = findMin(n->rchild_)->val_;
            RRemove(n->rchild_, n->val_);
        }
        else {
            // the node we want to remove has 1 or 0 children
            // delete the node and adjust the left or right child pointer
            Node * removeNode = n;
            // if the removeNode has no children, n will get set to null
            n = (n->lchild_ != nullptr) ? n->lchild_ : n->rchild_;
            delete removeNode;
        }
    }
}

template<typename T>
void BST<T>::Clear(BST::Node *&n) {
    if(n == nullptr)
        return;
    if(n->lchild_ != nullptr)
        Clear(n->lchild_);
    if(n->rchild_ != nullptr)
        Clear(n->rchild_);
    delete n;
    n = nullptr;
}

template<typename T>
bool BST<T>::RContains(BST::Node * n, const T &t) const {
    if(n == nullptr)
        return false;
    else if(t < n->val_)
        return RContains(n->lchild_, t);
    else if(t > n->val_)
        return RContains(n->rchild_, t);
    else
        return true;
}

template<typename T>
T & BST<T>::RGet(BST::Node * & n, const T &t) {
    if(n == nullptr) {
        // we have found where to insert t
        Node * newNode = CreateNode(t);
        n = newNode;
        return n->val_;
    }
    if(t < n->val_)
        return RGet(n->lchild_, t);
    else if(t > n->val_)
        return RGet(n->rchild_, t);
    else // t already in the tree
        return n->val_;
}

template<typename T>
void BST<T>::RPreOrder(BST::Node *n) const {
    if(n == nullptr) return;
    std::cout << n->val_ << ' ';
    RPreOrder(n->lchild_);
    RPreOrder(n->rchild_);
}

template<typename T>
void BST<T>::RInOrder(BST::Node *n) const {
    if(n == nullptr) return;
    RInOrder(n->lchild_);
    std::cout << n->val_ << ' ';
    RInOrder(n->rchild_);
}

template<typename T>
void BST<T>::RPostOrder(BST::Node *n) const {
    if(n == nullptr) return;
    RPostOrder(n->lchild_);
    RPostOrder(n->rchild_);
    std::cout << n->val_ << ' ';
}





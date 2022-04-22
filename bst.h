// Binary Search Tree
//
// Unimodal semantics - no duplicates allowed
//
// Created by Jason Ketterer on 4/21/22.
//

#ifndef BST_H
#define BST_H

#include <iostream>

template <typename T>
class BST {
public:
    BST() : root_(nullptr) {;}
    virtual ~BST();
    //BST & operator= (const BST & rhs);  // disabling assignment for now

    void Insert(const T & t);
    void Remove(const T & t);
    void Clear();

    size_t Height() const;
    size_t Size() const;

    void printHTree() const; // print horizontal tree
    void printVTree() const; // print vertical tree

protected:
    class Node {
        friend class BST<T>;

        T val_;
        Node * lchild_;
        Node * rchild_;

        explicit Node(const T & t) : val_(t), lchild_(nullptr), rchild_(nullptr) {;}
    };

    Node * root_;

    // internal memory allocator for new nodes in the list; centralize exception handling
    // we can also make the method static since it doesn't need access to any particular object's data
    static Node * CreateNode(const T & t);

    Node * findMin(Node * n) const;
    Node * findMax(Node * n) const;
    size_t RHeight(Node * n) const;
    size_t RSize(Node * n) const;
    void RInsert(Node * & n, const T & t);
    void RRemove(Node * & n, const T & t);

    void RPrintHTree(Node * n, int space) const;
    void printSpace(double n, Node * removed) const; // helper function for printVTree()
    void Clear(Node * & n);
};

#include "bst.cpp"

#endif //BST_H

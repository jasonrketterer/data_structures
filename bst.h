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

    void Dump (std::ostream& os, int dw, char fill) const;
    void Dump (std::ostream& os = std::cout) const;

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

    void RInsert(Node * & n, const T & t);
};

#include "bst.cpp"

#endif //BST_H

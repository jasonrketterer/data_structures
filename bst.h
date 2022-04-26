// Binary Search Tree
//
// Unimodal semantics - no duplicates allowed
//
// Created by Jason Ketterer on 4/21/22.
//

#ifndef BST_H
#define BST_H

#include <iostream>
#include "bst_iter.h"

template <class C>
class LevelOrderBTIterator;

template <typename T>
class BST {
public:
    typedef T ValueType;
    typedef LevelOrderBTIterator < BST<T> > LevelOrderIterator;

    BST() : root_(nullptr) {;}
    virtual ~BST();
    //BST & operator= (const BST & rhs);  // disabling assignment for now

    void Insert(const T & t);
    void Remove(const T & t);
    bool Contains(const T & t) const;
    T & Get(const T & t);  // inserts t if not in the tree
    void Clear();

    size_t Height() const;
    size_t Size() const;

    // standard traversals
    void PreOrder() const;
    void InOrder() const;
    void PostOrder() const;
    void LevelOrder() const;

    void minTree(Vector<T> & v);
    void listOfDepths(Vector< List<T> > & v);
    bool isBalanced() const;

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
    bool RContains(Node * n, const T & t) const;
    T & RGet(Node * & n, const T & t);

    void RPreOrder(Node * n) const;
    void RInOrder(Node * n) const;
    void RPostOrder(Node * n) const;

    void RPrintHTree(Node * n, int space) const;
    void printSpace(double n, Node * removed) const; // helper function for printVTree()

    void RMinTree(Node * & n, int s, int e, Vector<T> & v);
    bool RisBalanced(Node * n) const;

    void Clear(Node * & n);
};

#include "bst.cpp"

#endif //BST_H

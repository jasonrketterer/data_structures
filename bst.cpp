//
// Created by Jason Ketterer on 4/21/22.
//

#include <iostream>
#include "queue.h"
#include "bst.h"

template <typename T>
BST<T>::~BST() {
    ;
}

template <typename T>
void BST<T>::Insert(const T & t) {
    RInsert(root_, t);
}

template <typename T>
void BST<T>::Remove(const T & t) {
    ;
}

template < typename T >
void BST<T>::Dump (std::ostream& os, int dw, char fill) const
{
    // fsu::debug ("Dump(3)");
    if (root_ == nullptr)
        return;

    Node* fillNode = CreateNode(T());
    Queue < Node * > Que;
    Node * current;
    size_t currLayerSize, nextLayerSize, j, k;
    Que.Push(root_);
    currLayerSize = 1;
    k = 1;  // 2^LayerNumber
    while (currLayerSize > 0)
    {
        nextLayerSize = 0;
        if (dw == 1) os << ' '; // indent picture 1 space
        for (j = 0; j < k; ++j)
        {
            current = Que.Front();
            Que.Pop();
            if (dw > 1) os << ' '; // indent each column 1 space
            if (current == fillNode)
            {
                os << std::setw(dw) << fill;
            }
            else
            {
                os<< std::setw(dw) << current->val_;
            }

            if (current->lchild_)
            {
                Que.Push(current->lchild_);
                ++nextLayerSize;
            }
            else
            {
                Que.Push(fillNode);
            }
            if (current->rchild_)
            {
                Que.Push(current->rchild_);
                ++nextLayerSize;
            }
            else
            {
                Que.Push(fillNode);
            }
        }
        os << '\n';
        currLayerSize = nextLayerSize;
        k *= 2;
    } // end while
    //Que.Clear();
    delete fillNode;
}

template <typename T>
void BST<T>::Dump (std::ostream& os) const {
    if (root_ == nullptr)
        return;

    // we will use "root" as the placeholder node; test for dummy by address
    Queue <Node *> Que;
    char nullFill = '-';
    char nodeFill = '*';
    Node * fillNode = root_;
    Node * current;

    size_t currLayerSize, nextLayerSize, j, k;
    currLayerSize = 1;
    k = 1;  // 2^LayerNumber
    Que.Push(root_);

    // execute body once for "real" root:
    os << ' '; // 1-space left margin for graphic
    nextLayerSize = 0;
    current = Que.Front();
    Que.Pop();
    os << nodeFill;
    if (current->lchild_)
    {
        Que.Push(current->lchild_);
        ++nextLayerSize;
    }
    else
    {
        Que.Push(fillNode);
    }
    if (current->rchild_)
    {
        Que.Push(current->rchild_);
        ++nextLayerSize;
    }
    else
    {
        Que.Push(fillNode);
    }
    os << '\n';
    currLayerSize = nextLayerSize;
    k *= 2;

    // now finish off, using address to detect fillNode.
    while (currLayerSize > 0)
    {
        nextLayerSize = 0;
        os << ' '; // 1-space left margin for graphic
        for (j = 0; j < k; ++j)
        {
            current = Que.Front();
            Que.Pop();
            if (current == fillNode) // an empty position in the tree
                os << nullFill;
            else
                os << nodeFill;
            if (current != fillNode && current->lchild_)
            {
                Que.Push(current->lchild_);
                ++nextLayerSize;
            }
            else
            {
                Que.Push(fillNode);
            }
            if (current != fillNode && current->rchild_)
            {
                Que.Push(current->rchild_);
                ++nextLayerSize;
            }
            else
            {
                Que.Push(fillNode);
            }
        } // end for
        os << '\n';
        currLayerSize = nextLayerSize;
        k *= 2;
    } // end while
    //Que.Clear();
} // Dump(os)

/*************************************
 * Protected methods
 *************************************/

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

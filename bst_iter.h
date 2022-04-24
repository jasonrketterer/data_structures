//
// Created by Jason Ketterer on 4/22/22.
//

#ifndef BST_ITER_H
#define BST_ITER_H

#include "queue.h"

template <class C>
class LevelOrderBTIterator {
public:
    typedef typename C::ValueType ValueType;
    typedef typename C::Node Node;
    typedef LevelOrderBTIterator<C> ConstIterator;
    typedef LevelOrderBTIterator<C> Iterator;

    LevelOrderBTIterator();
    ~LevelOrderBTIterator();

private:
    friend C;
    Queue<Node *> q_;
    void Init(Node * n);
};

#endif //BST_ITER_H

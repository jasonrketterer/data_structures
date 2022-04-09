//
// Created by Jason Ketterer on 4/9/22.
//

#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

template <typename T>
class Queue {
public:
    // no constructor; List constructor will be called by default

    void Push(const T & t) { q.PushBack(t); } // add t to back of queue
    void Pop() { q.PopFront(); } // remove item from front of the list
    T & Front() { return q.Front(); } // return item at front of the queue
    const T & Front() const { return q.Front(); } // const version
    bool Empty() const { return q.Empty(); }
    size_t Size() const { return q.Size(); } // # of items in the queue
    void Display(std::ostream & os) {
        os << "front -> ";
        q.Display(os);
    }

private:
    List<T> q;
};

#endif //QUEUE_H

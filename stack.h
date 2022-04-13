//
// Created by Jason Ketterer on 4/9/22.
//

#ifndef STACK_H
#define STACK_H

#include "list.h"

template <typename T>
class Stack {
public:
    // no constructor; List constructor will handle initialization

    void Push(const T & t) { stack.PushFront(t); }
    void Pop() {
        if(stack.Empty()) {
            std::cerr << "**Pop called on empty stack\n";
        }
        stack.PopFront();
    }
    T & Top() {
        if(stack.Empty()) {
            std::cerr << "**Top called on empty stack\n";
        }
        return stack.Front();
    }
    const T & Top() const {
            if(stack.Empty()) {
                std::cerr << "**Top called on empty stack\n";
                return;
            }
            return stack.Front();
    }
    bool Empty() const { return stack.Empty(); }
    size_t Size() const { return stack.Size(); }
    void Display(std::ostream & os = std::cout) {
        os << "top -> ";
        stack.Display(os);
    }

private:
    List<T> stack;
};

#endif //STACK_H

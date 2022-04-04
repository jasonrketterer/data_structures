//
// Created by Jason Ketterer on 4/4/22.
//

#ifndef LIST_H
#define LIST_H

#include <iostream>

template <typename T>
class ListIterator;

template <typename T>
class List {
public:
    typedef ListIterator<T> Iterator;

    List();
    ~List();
    //List & operator=(const List &); // assignment

    void PushBack(const T & t);
    Iterator Insert(Iterator i, const T & t);

    bool PopFront();
    bool PopBack();
    Iterator Remove(Iterator i);
    void Clear();

    //void Reverse();

    size_t Size() const;
    bool Empty() const;

    void Display(std::ostream & os, char ofc = '\0') const;

protected:
    class Node {
        friend class List<T>;
        friend class ListIterator<T>;

        T val_;
        Node * prev_;
        Node * next_;

        Node(const T & t) : val_(t), prev_(nullptr), next_(nullptr);
    };

    Node * head_;
    Node * tail_;
    size_t size_;

    friend class ListIterator<T>;
};

template <typename T>
class ListIterator {
    typedef ListIterator<T> Iterator;

    ListIterator();
};

#include "list.cpp"

#endif //LIST_H

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
    //Iterator Insert(Iterator i, const T & t);

    bool PopFront();
    bool PopBack();
    //Iterator Remove(Iterator i);
    void Clear();

    void Reverse();

    size_t Size() const;
    bool Empty() const;

    // Iterator support
    Iterator Begin();
    Iterator End();

    void Display(std::ostream & os, char ofc = '\0') const;

protected:
    class Node {
        friend class List<T>;
        friend class ListIterator<T>;

        T val_;
        Node * prev_;
        Node * next_;

        explicit Node(const T & t) : val_(t), prev_(nullptr), next_(nullptr) {}
    };

    Node * head_;
    Node * tail_;
    size_t size_;

    friend class ListIterator<T>;
};

template <typename T>
class ListIterator {
public:
    typedef ListIterator<T> Iterator;

    ListIterator();
    ListIterator(const Iterator & i);

    bool operator == (const ListIterator& i2) const;
    bool operator != (const ListIterator& i2) const;
    T & operator * ();
    const T & operator * () const;
    ListIterator & operator = (const ListIterator & i);
    ListIterator & operator ++ (); // prefix
    ListIterator operator ++ (int); // postfix

protected:
    typename List<T>::Node * curr_;

    friend class List<T>;
};

#include "list.cpp"

#endif //LIST_H

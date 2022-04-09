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

    void PushFront(const T & t);
    void PushBack(const T & t);
    Iterator Insert(Iterator i, const T & t);

    bool PopFront();
    bool PopBack();
    Iterator Remove(Iterator i);
    void Clear();

    void Reverse();

    size_t Size() const;
    bool Empty() const;

    // access values in the List
    T & Front();
    const T & Front() const;
    T & Back();
    const T & Back() const;

    // Iterator support
    Iterator Begin();  // return iterator to front
    Iterator End();    // 1 past the back
    Iterator rBegin(); // return iterator to back
    Iterator rEnd();   // 1 past the front

    void Display(std::ostream & os, char ofc = '\0') const;
    void Dump(std::ostream & os) const;

    friend class ListIterator<T>;

protected:
    class Node {
        friend class List<T>;
        friend class ListIterator<T>;

        T val_;
        Node * prev_;
        Node * next_;

        explicit Node(const T & t) : val_(t), prev_(nullptr), next_(nullptr) {}

        friend class ListIterator<T>;
    };

    Node * head_;
    Node * tail_;
    size_t size_;
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
    ListIterator & operator -- (); // prefix
    ListIterator operator -- (int); // postfix

    void Dump() const;

protected:
    typename List<T>::Node * curr_;

    friend class List<T>;
};

#include "list.cpp"

#endif //LIST_H

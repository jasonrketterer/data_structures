// STL-like Linked List
//
// Doubly linked list with iterator support
//
// Uses sentinel nodes for the head and tail
// so that we can support bidirectional iterators.
//
// Unlike the STL std::list, this list is non-circular.
// Incrementing/decrementing past either end or attempting to
// dereference the head or tail node will throw an error.
// It is up to the client to "know where they are" in the list by
// using the iterator support.
//
// Created by Jason Ketterer on 4/4/22.
//

#ifndef LIST_H
#define LIST_H

#include <iostream>

template <typename T>
class ListIterator;

template <typename T>
class ConstListIterator;

template <typename T>
class List {
public:
    typedef ListIterator<T> Iterator;
    typedef ConstListIterator<T> ConstIterator;

    List();
    virtual ~List();
    List & operator=(const List & rhs); // assignment

    void PushFront(const T & t);
    void PushBack(const T & t);
    Iterator Insert(Iterator i, const T & t);
    ConstIterator Insert(ConstIterator i, const T & t);

    List & operator+=(const List & list);  // append a (deep) copy of list

    bool PopFront();
    bool PopBack();
    Iterator Remove(Iterator i);
    void Clear();

    void Sort();
    void Reverse();
    void removeDuplicates();

    void sumLists(List<T> & list1, List<T> & list2);

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

    // ConstIterator support
    ConstIterator Begin() const;
    ConstIterator End() const;
    ConstIterator rBegin() const;
    ConstIterator rEnd() const;

    void Display(std::ostream & os = std::cout, char ofc = '\0') const;
    void Dump(std::ostream & os = std::cout) const; // displays detailed address info about each node

    friend class ListIterator<T>;

protected:
    class Node {
        friend class List<T>;
        friend class ListIterator<T>;
        friend class ConstListIterator<T>;

        T val_;
        Node * prev_;
        Node * next_;

        explicit Node(const T & t) : val_(t), prev_(nullptr), next_(nullptr) {}
    };

    // List data members
    Node * head_;
    Node * tail_;
    size_t size_;

    // internal memory allocator for new nodes in the list; centralize exception handling
    // we can also make the method static since it doesn't need access to any particular object's data
    static Node * CreateNode(const T & t);

    // add the nodes in list to the end of this list
    void Append(const List<T> & list);


    friend class ListIterator<T>;
    friend class ConstListIterator<T>;
};

// global scope operators

template <typename T>
bool operator == (const List<T>& list1, const List<T>& list2);

template <typename T>
bool operator != (const List<T>& list1, const List<T>& list2);

template <typename T>
std::ostream& operator << (std::ostream& os, const List<T>& list);

template <typename T>
class ConstListIterator {
public:
    typedef ConstListIterator<T> ConstIterator;

    ConstListIterator();
    ConstListIterator(const ConstIterator & i);
    ConstListIterator & operator = (const ConstListIterator & i);

    bool Valid() const;  // checks Iterator pointer before de-referencing

    bool operator == (const ConstListIterator& i2) const;
    bool operator != (const ConstListIterator& i2) const;
    const T & operator * () const;
    ConstListIterator & operator ++ (); // prefix
    const ConstListIterator operator ++ (int); // postfix
    ConstListIterator & operator -- (); // prefix
    const ConstListIterator operator -- (int); // postfix

protected:
    typename List<T>::Node * curr_;

    void Dump() const;

    static std::string invalid_iter_error_msg;

    friend class List<T>;
};

template <typename T>
class ListIterator : public ConstListIterator<T> {
public:
    typedef ListIterator<T> Iterator;
    typedef ConstListIterator<T> ConstIterator;

    ListIterator();
    ListIterator(const Iterator & i);

    // commented methods are inherited

    //bool operator == (const ListIterator& i2) const;
    //bool operator != (const ListIterator& i2) const;
    T & operator * ();
    const T & operator * () const;
    ListIterator & operator = (const ListIterator & i);
    ListIterator & operator ++ (); // prefix
    const ListIterator operator ++ (int); // postfix
    ListIterator & operator -- (); // prefix
    const ListIterator operator -- (int); // postfix

    //bool Valid() const;  // checks Iterator pointer before de-referencing

protected:

    //void Dump() const;

    friend class List<T>;
};

#include "list.cpp"

#endif //LIST_H

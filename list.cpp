//
// Created by Jason Ketterer on 4/4/22.
//

#include "list.h"

template <typename T>
List<T>::List() : head_(0), tail_(0), size_(0) {;}

template <typename T>
List<T>::~List() {
    Clear();
    head_ = tail_ = 0;
}

template <typename T>
void List<T>::Clear() {
    while(!Empty())
        PopFront();
}

// reverse nodes in place
template <typename T>
void List<T>::Reverse() {
    if(Empty() || Size() == 1)
        return;
    Node * curr, * temp;
    curr = head_;
    while(curr != nullptr) {
        temp = curr->next_;
        curr->next_ = curr->prev_;
        curr->prev_ = temp;
        curr = temp;
    }
    temp = head_;
    head_ = tail_;
    tail_ = temp;
}

template <typename T>
bool List<T>::Empty() const {
    return head_ == 0;
}

template <typename T>
void List<T>::PushBack(const T & t) {
    Node * newNode = new Node(t);
    if(Empty()) {
        head_ = tail_ = newNode;
    }
    else {
        tail_->next_ = newNode;
        newNode->prev_ = tail_;
        tail_ = newNode;
    }
    ++size_;
}

template <typename T>
bool List<T>::PopFront() {
    if(Empty())
        return false;
    if(Size() == 1) {
        //temp = head_;
        delete head_;
        head_ = tail_ = 0;
    }
    else {
        Node * temp;
        temp = head_->next_;
        delete head_;
        head_ = temp;
        temp->prev_ = head_;
    }
    --size_;
    return true;
}

template <typename T>
bool List<T>::PopBack() {
    if(Empty())
        return false;
    if(Size() == 1) {
        //temp = head_;
        delete head_;
        head_ = tail_ = 0;
    }
    else {
        Node * temp;
        temp = tail_->prev_;
        delete tail_;
        tail_ = temp;
        tail_->next_ = nullptr;
    }
    --size_;
    return true;
}

template <typename T>
size_t List<T>::Size() const {
    return size_;
}

template <typename T>
ListIterator<T> List<T>::Begin() {
    Iterator i;
    i.curr_ = head_;
    return i;
}

template <typename T>
ListIterator<T> List<T>::End() {
    Iterator i;
    i.curr_ = tail_->next_;
    return i;
}

template <typename T>
void List<T>::Display(std::ostream & os, char ofc) const {
    Node * curr = head_;
    while(curr != nullptr) {
        std::cout << curr->val_ << ' ';
        curr = curr->next_;
    }
    std::cout << std::endl;
}

template <typename T>
ListIterator<T>::ListIterator() : curr_(nullptr){;}

template <typename T>
ListIterator<T>::ListIterator(const Iterator & i) : curr_(i.curr_){;}

template <typename T>
bool ListIterator<T>::operator == (const ListIterator& i2) const {
    return curr_ == i2.curr_;
}

template <typename T>
bool ListIterator<T>::operator != (const ListIterator& i2) const {
    return !(*this == i2);
}

template <typename T>
T & ListIterator<T>::operator * () {
    if(curr_ != nullptr)
        return curr_->val_;
}

template <typename T>
const T & ListIterator<T>::operator * () const {
    if(curr_ != nullptr)
        return curr_->val_;
}

template <typename T>
ListIterator<T> & ListIterator<T>::operator = (const Iterator & i) {
    curr_ = i.curr_;
    return *this;
}

template <typename T>
ListIterator<T> & ListIterator<T>::operator ++ () {
    if(curr_ != nullptr)
        curr_ = curr_->next_;
    return *this;
}

template <typename T>
ListIterator<T> ListIterator<T>::operator ++ (int) {
    ListIterator<T> copy = *this;
    if(curr_ != nullptr)
        curr_ = curr_->next_;
    return copy;
}
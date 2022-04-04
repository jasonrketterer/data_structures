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
void List<T>::Display(std::ostream & os, char ofc) const {
    Node * curr = head_;
    while(curr != nullptr) {
        std::cout << curr->val_ << ' ';
        curr = curr->next_;
    }
    std::cout << std::endl;
}
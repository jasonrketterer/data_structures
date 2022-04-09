// Linked List
//
// Doubly linked list with sentinel nodes for
// the head and tail.  Iterator support included.
//
// Created by Jason Ketterer on 4/4/22.
//

#include "list.h"

template <typename T>
List<T>::List() : head_(nullptr), tail_(nullptr), size_(0) {
    head_ = new Node(T());
    tail_ = new Node(T());
    head_->next_ = tail_;
    tail_->prev_ = head_;
}

template <typename T>
List<T>::~List() {
    Clear();
    delete head_;
    delete tail_;
}

template <typename T>
void List<T>::Clear() {
    while(!Empty())
        PopFront();
}

// reverse nodes in place
template <typename T>
void List<T>::Reverse() {
    if(Empty())
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
    return head_->next_ == tail_;
}

template <typename T>
void List<T>::PushFront(const T & t) {
    Node * newNode = new Node(t);
    head_->next_->prev_ = newNode;
    newNode->next_ = head_->next_;
    head_->next_ = newNode;
    newNode->prev_ = head_;
    ++size_;
}

template <typename T>
void List<T>::PushBack(const T & t) {
    Node * newNode = new Node(t);
    tail_->prev_->next_ = newNode;
    newNode->prev_ = tail_->prev_;
    tail_->prev_ = newNode;
    newNode->next_ = tail_;
    ++size_;
}

template <typename T>
ListIterator<T> List<T>::Insert(Iterator i, const T & t) {
    if(i == Begin() || i.curr_ == head_) {
        PushFront(t);
        i.curr_ = head_->next_;
        return i;
    }
    if(i == End() || i.curr_ == tail_->prev_) {
        PushBack(t);
        i.curr_ = tail_->prev_;
        return i;
    }
    Node * newNode = new Node(t);
    newNode->prev_ = i.curr_;
    newNode->next_ = i.curr_->next_;
    newNode->next_->prev_ = newNode;
    newNode->prev_->next_ = newNode;
    i.curr_ = newNode;
    ++size_;
    return i;
}

template <typename T>
bool List<T>::PopFront() {
    if(Empty())
        return false;
    Node * temp = head_->next_;
    temp->next_->prev_ = head_;
    head_->next_ = temp->next_;
    delete temp;
    --size_;
    return true;
}

template <typename T>
bool List<T>::PopBack() {
    if(Empty())
        return false;
    Node * temp = tail_->prev_;
    temp->prev_->next_ = tail_;
    tail_->prev_ = temp->prev_;
    delete temp;
    --size_;
    return true;
}

template <typename T>
ListIterator<T> List<T>::Remove(ListIterator<T> i) {
    if(i.curr_ == nullptr || i.curr_ == head_ || i.curr_ == tail_) {
        std::cerr << "Remove() called on invalid iterator\n";
        return i;
    }
    Node * temp = i.curr_;
    i.curr_ = i.curr_->next_;
    i.curr_->prev_ = temp->prev_;
    temp->prev_->next_ = i.curr_;
    delete temp;
    --size_;
    return i;
}

template <typename T>
size_t List<T>::Size() const {
    return size_;
}

template <typename T>
T & List<T>::Front() {
    if(Empty()) {
        std::cerr << "**Front() called on empty list\n";
        exit(EXIT_FAILURE);
    }
    return head_->next_->val_;
}

template <typename T>
const T & List<T>::Front() const{
    if(Empty()) {
        std::cerr << "**Front() called on empty list\n";
        exit(EXIT_FAILURE);
    }
    return head_->next_->val_;
}

template <typename T>
T & List<T>::Back() {
    if(Empty()) {
        std::cerr << "**Back() called on empty list\n";
        exit(EXIT_FAILURE);
    }
    return tail_->prev_->val_;
}

template <typename T>
const T & List<T>::Back() const{
    if(Empty()) {
        std::cerr << "**Back() called on empty list\n";
        exit(EXIT_FAILURE);
    }
    return tail_->prev_->val_;
}

template <typename T>
ListIterator<T> List<T>::Begin() {
    Iterator i;
    i.curr_ = head_->next_;
    return i;
}

template <typename T>
ListIterator<T> List<T>::End() {
    Iterator i;
    i.curr_ = tail_;
    return i;
}

template <typename T>
ListIterator<T> List<T>::rBegin() {
    Iterator i;
    i.curr_ = tail_->prev_;
    return i;
}

template <typename T>
ListIterator<T> List<T>::rEnd() {
    Iterator i;
    i.curr_ = head_;
    return i;
}

template <typename T>
void List<T>::Display(std::ostream & os, char ofc) const {
    std::cout << "[ ";
    Node * curr = head_->next_;
    while(curr != tail_) {
        os << curr->val_ << ' ';
        curr = curr->next_;
    }
    std::cout << ']';
    os << std::endl;
}

template <typename T>
void List<T>::Dump(std::ostream &os) const {
    os << "Head: " << head_ << '\n';
    os << "prev: " << head_->prev_ << '\n';
    os << "next: " << head_->next_ << "\n\n";

    Node * nodePtr = head_->next_;
    for(size_t i = 1; nodePtr != tail_; ++i, nodePtr = nodePtr->next_) {
        os << "Node " << i << ": " << nodePtr << '\n';
        os << "prev: " << nodePtr->prev_ << '\n';
        os << "val: " << nodePtr->val_ << '\n';
        os << "next: " << nodePtr->next_ << "\n\n";
    }

    os << "Tail: " << tail_ << '\n';
    os << "prev: " << tail_->prev_ << '\n';
    os << "next: " << tail_->next_ << "\n\n";
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
    ++*this;
    return copy;
}

template <typename T>
ListIterator<T> & ListIterator<T>::operator -- () {
    if(curr_ != nullptr)
        curr_ = curr_->prev_;
    return *this;
}

template <typename T>
ListIterator<T> ListIterator<T>::operator -- (int) {
    ListIterator<T> copy = *this;
    --*this;
    return copy;
}

template <typename T>
void ListIterator<T>::Dump() const {
    std::cout << "Iterator's curr address: " << curr_ << '\n';
}
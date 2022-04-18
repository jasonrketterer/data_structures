//
// Created by Jason Ketterer on 4/4/22.
//

#include "list.h"



template <typename T>
List<T>::List() : head_(nullptr), tail_(nullptr), size_(0) {
    head_ = CreateNode(T());
    tail_ = CreateNode(T());
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
    // swap head and tail
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
    Node * newNode = CreateNode(t);

    // since head and tail are themselves nodes, no need to check for empty first
    head_->next_->prev_ = newNode;
    newNode->next_ = head_->next_;
    head_->next_ = newNode;
    newNode->prev_ = head_;

    ++size_;
}

template <typename T>
void List<T>::PushBack(const T & t) {
    Node * newNode = CreateNode(t);

    // since head and tail are themselves nodes, no need to check for empty first
    tail_->prev_->next_ = newNode;
    newNode->prev_ = tail_->prev_;
    tail_->prev_ = newNode;
    newNode->next_ = tail_;

    ++size_;
}

// insert t in front of i
// returns an iterator to the newly inserted element; points the argument iterator
// to the first element past the newly inserted element
template <typename T>
ListIterator<T> List<T>::Insert(Iterator & i, const T & t) {
    if(!i.Valid() || i == rBegin()) {
        std::cerr << "**Cannot insert at position pointed to by iterator\n";
        return End();
    }
    Node * newNode = CreateNode(t);
    newNode->prev_ = i.curr_;
    newNode->next_ = i.curr_->next_;
    newNode->next_->prev_ = newNode;
    newNode->prev_->next_ = newNode;
    i.curr_ = newNode->next_;
    ++size_;

    Iterator iNew;
    iNew.curr_ = newNode;
    return iNew;
}

template <typename T>
bool List<T>::PopFront() {
    if(Empty()) {
        std::cerr << "**PopFront called on empty List\n";
        return false;
    }
    Node * temp = head_->next_;
    temp->next_->prev_ = head_;
    head_->next_ = temp->next_;
    delete temp;
    --size_;
    return true;
}

template <typename T>
bool List<T>::PopBack() {
    if(Empty()) {
        std::cerr << "**PopBack called on empty List\n";
        return false;
    }
    Node * temp = tail_->prev_;
    temp->prev_->next_ = tail_;
    tail_->prev_ = temp->prev_;
    delete temp;
    --size_;
    return true;
}

template <typename T>
ListIterator<T> List<T>::Remove(ListIterator<T> i) {
    if(i.curr_ == nullptr || i == End() || i == rEnd()) {
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
ConstListIterator<T> List<T>::Begin() const {
    ConstIterator i;
    i.curr_ = head_->next_;
    return i;
}

template <typename T>
ConstListIterator<T> List<T>::End() const {
    ConstIterator i;
    i.curr_ = tail_;
    return i;
}

template <typename T>
ConstListIterator<T> List<T>::rBegin() const {
    ConstIterator i;
    i.curr_ = tail_->prev_;
    return i;
}

template <typename T>
ConstListIterator<T> List<T>::rEnd() const {
    ConstIterator i;
    i.curr_ = head_;
    return i;
}

template <typename T>
void List<T>::Display(std::ostream & os, char ofc) const {
    if(!Empty()) {
        //os << "[ ";
        Node *curr = head_->next_;
        while (curr != tail_->prev_) {
            os << curr->val_ << " , ";
            curr = curr->next_;
        }
        os << curr->val_ << '\n';
        //os << ']';
        //os << std::endl;
    }
    else
        std::cout << std::endl;
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
typename List<T>::Node * List<T>::CreateNode(const T & t) {
    Node * newNode = new(std::nothrow) Node(t);
    if(newNode == nullptr) {
        std::cerr << "**Unable to allocate memory for new Node\n";
        return nullptr;
    }
    return newNode;
}

/*********************************************
 *   ConstListIterator implementations
 *********************************************/

template <typename T>
std::string ConstListIterator<T>::invalid_iter_error_msg = "**Operation called on invalid iterator";

template <typename T>
ConstListIterator<T>::ConstListIterator() : curr_(nullptr)
{;}

template <typename T>
ConstListIterator<T>::ConstListIterator(const ConstIterator & i) : curr_(i.curr_)
{;}

template <typename T>
bool ConstListIterator<T>::operator == (const ConstListIterator& i2) const {
    return curr_ == i2.curr_;
}

template <typename T>
bool ConstListIterator<T>::operator != (const ConstListIterator& i2) const {
    return !(*this == i2);
}

template <typename T>
const T & ConstListIterator<T>::operator * () const {
    if(Valid())
        return curr_->val_;
}

template <typename T>
ConstListIterator<T> & ConstListIterator<T>::operator = (const ConstIterator & i) {
    curr_ = i.curr_;
    return *this;
}

template <typename T>
ConstListIterator<T> & ConstListIterator<T>::operator ++ () {
    if(Valid())
        curr_ = curr_->next_;
    return *this;
}

template <typename T>
const ConstListIterator<T> ConstListIterator<T>::operator ++ (int) {
    ConstListIterator<T> copy = *this;
    (*this).operator++();
    return copy;
}

template <typename T>
ConstListIterator<T> & ConstListIterator<T>::operator -- () {
    if(Valid())
        curr_ = curr_->prev_;
    return *this;
}

template <typename T>
const ConstListIterator<T> ConstListIterator<T>::operator -- (int) {
    ListIterator<T> copy = *this;
    (*this).operator--();
    return copy;
}

template <typename T>
bool ConstListIterator<T>::Valid() const {
    if(curr_ == nullptr) {
        std::cerr << invalid_iter_error_msg << "\n";
        //exit(EXIT_FAILURE);
        return false;
    }
    return true;
}

template <typename T>
void ConstListIterator<T>::Dump() const {
    std::cout << "Iterator's curr address: " << curr_ << '\n';
}

/*********************************************
 *   ListIterator implementations
 *********************************************/

template <typename T>
ListIterator<T>::ListIterator() : ConstListIterator<T>()
{;}

template <typename T>
ListIterator<T>::ListIterator(const Iterator & i) : ConstListIterator<T>(i)
{;}

template <typename T>
T & ListIterator<T>::operator * () {
    if(ConstListIterator<T>::Valid())
        return ConstListIterator<T>::curr_->val_;
}

template <typename T>
const T & ListIterator<T>::operator * () const {
    if(ConstListIterator<T>::Valid())
        return ConstListIterator<T>::curr_->val_;
}

template <typename T>
ListIterator<T> & ListIterator<T>::operator = (const Iterator & i) {
    ConstListIterator<T>::operator=(i);
    return *this;
}

template <typename T>
ListIterator<T> & ListIterator<T>::operator ++ () {
    ConstListIterator<T>::operator++();
    return *this;
}

template <typename T>
const ListIterator<T> ListIterator<T>::operator ++ (int) {
    ListIterator<T> copy = *this;
    this->operator++();
    return copy;
}

template <typename T>
ListIterator<T> & ListIterator<T>::operator -- () {
    ConstListIterator<T>::operator--();
    return *this;
}

template <typename T>
const ListIterator<T> ListIterator<T>::operator -- (int) {
    ListIterator<T> copy = *this;
    this->operator--();
    return copy;
}



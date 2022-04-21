//
// Created by Jason Ketterer on 4/4/22.
//

#include "list.h"
#include <map>

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
List<T> & List<T>::operator=(const List & rhs) {
    if(this != &rhs) {
        Clear();
        Append(rhs);
    }
    return *this;
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

// in place sort, O(n_^2)
template <typename T>
void List<T>::Sort() {
    // maintain 2 iterators: 1 to iterate through list, 1 for insert position
    ListIterator<T> i, insertPosition;
    T largest; int n;

    insertPosition = End();
    for(n = 1, i = Begin(), largest = *i; n <= Size(); ++n) {
        for(++i; i != insertPosition; ++i) { ;
        }
    }
}

template <typename T>
void List<T>::removeDuplicates() {
    std::map<T,bool> dupmap;
    std::pair<std::map<int,bool>::iterator, bool> result;
    ListIterator<int> i = Begin();
    while(i != End()) {
        result = dupmap.insert(std::pair<T,bool>(*i, true));
        if(result.second == false) // key was already added, i.e. a duplicate exists
            i = Remove(i);
        else
            ++i;
    }
}

template <typename T>
void List<T>::sumLists(List<T> & list1, List<T> & list2) {
    List<T> result;
    int sum, carry = 0;
    ListIterator<T> i1, i2;
    for(i1=list1.rBegin(), i2=list2.rBegin(); i1!=list1.rEnd(); --i1, --i2) {
        sum = *i1 + *i2 + carry;
        if(sum > 9) {
            sum -= 10;
            carry = 1;
        }
        else
            carry = 0;
        result.PushFront(sum);
    }
    if (carry) result.PushBack(carry);
    std::cout << result;
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

// insert t behind i
// returns an iterator to the newly inserted element;
// argument iterator still points to the same element behind which we inserted
template <typename T>
ListIterator<T> List<T>::Insert(Iterator i, const T & t) {
    if(!i.Valid() || i == rBegin()) {
        std::cerr << "**Cannot insert at position pointed to by iterator\n";
        return End();
    }
    Node * newNode = CreateNode(t);
    newNode->next_ = i.curr_;
    newNode->prev_ = i.curr_->prev_;
    i.curr_->prev_->next_ = newNode;
    i.curr_->prev_ = newNode;

    ++size_;

    Iterator iNew;
    iNew.curr_ = newNode;
    return iNew;
}

// insert t behind i
// returns an iterator to the newly inserted element;
// argument iterator still points to the same element behind which we inserted
template <typename T>
ConstListIterator<T> List<T>::Insert(ConstIterator i, const T & t) {
    if(!i.Valid() || i == rBegin()) {
        std::cerr << "**Cannot insert at position pointed to by iterator\n";
        return End();
    }
    Node * newNode = CreateNode(t);
    newNode->next_ = i.curr_;
    newNode->prev_ = i.curr_->prev_;
    i.curr_->prev_->next_ = newNode;
    i.curr_->prev_ = newNode;

    ++size_;

    ConstIterator iNew;
    iNew.curr_ = newNode;
    return iNew;
}

template <typename T>
List<T> & List<T>::operator+=(const List & list) {
    if(this != &list)  // can't append to self, otherwise we'll enter infinite loop
        Append(list);
    return *this;
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

template <typename T>
void List<T>::Append(const List<T> & list) {
    ConstIterator i = list.Begin();
    for(; i != list.End(); ++i)
        PushBack(*i);
}

template <typename T>
bool operator == (const List<T>& list1, const List<T>& list2) {
    if(list1.Size() != list2.Size())
        return false;

    ConstListIterator<T> i1, i2;
    for(i1 = list1.Begin(), i2 = list2.Begin(); i1 != list1.End(); ++i1, ++i2)
        if(*i1 != *i2)
            return false;
    return true;
}

template <typename T>
bool operator != (const List<T>& list1, const List<T>& list2) {
    return !(list1 == list2);
}

template <typename T>
std::ostream& operator << (std::ostream& os, const List<T>& list) {
    list.Display(os);
    return os;
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



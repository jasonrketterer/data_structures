#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <vector>
#include "vector.h"
#include "list.h"
#include "stack.h"
#include "queue.h"
#include "graph.h"
#include "bst.h"
#include "list_test.h"

class Link {
    friend class LinkedList;
public:
    int val;
    Link * next;

    explicit Link(int d = 0) : val(d), next(nullptr) {;}
};

class LinkedList {
public:
    friend class Link;

    Link * head;

    LinkedList() : head(nullptr) {}

    void pushFront(int val) {
        Link * newLink = new Link(val);
        if(head == nullptr) {
            head = newLink;
            return;
        }
        newLink->next = head;
        head = newLink;
    }

    // insert in front of link; return pointer to new link
    Link * insert(Link * & link, int val) {
        if(link == nullptr)
            return nullptr; // insert nothing
        if(link == head) {
            pushFront(val);
            return head;
        }
        Link * newLink = new Link(val);
        Link * temp = link->next;
        link->next = newLink;
        newLink->next = temp;
        return newLink;
    }

    // delete val;
    void remove(int val) {
        Link * curr = head, * temp;
        if(curr->val == val) {
            temp = curr;
            head = curr->next;
            delete temp;
            return;
        }
        while(curr->next != nullptr) {
            if(curr->next->val == val) {
                temp = curr->next;
                curr->next = curr->next->next;
                delete temp;
                return;
            }
            curr = curr->next;
        }
    }

    void printList() const {
        Link * curr = head;
        while(curr != nullptr) {
            std::cout << curr->val << ' ';
            curr = curr->next;
        }
        std::cout << '\n';
    }
};

void assertTest(int n) {
    assert((n == 0));
}

int main() {


    BST<int> t;
    t.Insert(8); t.Insert(1); t.Insert(12);
    t.Insert(5); t.Insert(0); t.Insert(4);
    t.Insert(6);  t.Insert(10); t.Insert(11);
    t.Insert(9); t.Insert(13); t.Insert(14);
    t.printVTree();
    t.InOrder();
    //std::cout << "\nTree height is " << t.Height() << '\n';
    //std::cout << "The number of nodes is " << t.Size() << '\n';
    assertTest(0);
    //assertTest(1);

    /*
    int myints[] = {75,23,65,42,13};
    std::list<int> mylist (myints,myints+5);

    std::cout << "mylist contains:";
    std::list<int>::iterator it;
    for (it=mylist.begin() ; it != mylist.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
    it = mylist.begin();
    mylist.insert(it,0);
    std::cout << *it << '\n';
    for (it=mylist.begin() ; it != mylist.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
    */
}

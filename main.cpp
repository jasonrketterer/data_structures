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

std::vector< std::list<int> > findWays(int steps, std::vector<int> & hops) {
    static std::map< int, std::vector< std::list<int> > > memo;

    if(steps == 0) {
        std::vector<std::list<int> > empty;
        return empty;
    }
    if(steps < 0) {
        std::vector< std::list<int> > null;
        null[0].push_back(-1);
        return null;
    }

    for(auto i : hops) {
        int diff = steps - hops[i];
        std::vector< std::list<int> > result;
        result = findWays(diff, hops);
        if(result[0].front() != -1) { // not null
            std::list<int> l;
            result.push_back(l);
            result[result.size()-1].push_front(i);
            return result;
        }
    }
    std::vector< std::list<int> > null;
    null[0].push_back(-1);
    return null;
};

std::list< std::vector<int> > findWaysTab(int steps, std::vector<int> & hops) {
    std::vector< std::list< std::vector<int> > * > table(steps + 1, nullptr);

    table[0] = new std::list<std::vector<int>>;

    for(int i = 0; i < table.size(); ++i) {

    }
}

int main() {
    std::vector<int> hops = {1,2,3};
    int steps = 8;

    std::list< std::vector<int> > result = findWaysTab(steps, hops);


    /*
    BST<int> t;
    t.Insert(8); t.Insert(1); t.Insert(12);
    t.Insert(5); t.Insert(0); t.Insert(4);
    t.Insert(6);  t.Insert(10); t.Insert(11);
    t.Insert(9); t.Insert(13); t.Insert(14);
    t.printVTree();
    t.InOrder();
    //std::cout << "\nTree height is " << t.Height() << '\n';
    //std::cout << "The number of nodes is " << t.Size() << '\n';
    */
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

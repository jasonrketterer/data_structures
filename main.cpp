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

int main() {
    List<int> l;
    l.PushBack(1); l.PushBack(2); l.PushBack(3);
    ConstListIterator<int> i = l.Begin();
    ListIterator<int> j = l.Begin();
    i = j;
    std::cout << *i << '\n';

    /*
    std::list<int> l1(5);
    std::list<int>::iterator i1 = l1.begin();
    std::list<int>::const_iterator i2 = l1.begin();
    i1 = i2;
    *i2;

    ConstListIterator<int> j = l.Begin();
    std::cout << *i << ' ' << *j << '\n';
    if( i == j)
        std::cout << "the iterators are equal\n";
        */
    /*
    int myints[] = {75,23,65,42,13};
    std::list<int> mylist (myints,myints+5);

    std::cout << "mylist contains:";
    std::list<int>::iterator it;
    for (it=mylist.begin() ; it != mylist.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
    mylist.insert(it,0);
    for (it=mylist.begin() ; it != mylist.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
    */
}

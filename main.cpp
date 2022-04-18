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
    l.PushFront(0); l.PushBack(1); l.PushBack(2); l.PushBack(3);
    ListIterator<int> i = l.Begin(); ++i;
    l.Insert(i,0);
    std::cout << *i << '\n';

    for(ListIterator<int> j = l.Begin(); j != l.End(); ++j)
        std::cout << *j << ' ';
    std::cout << '\n';

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

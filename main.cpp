#include <iostream>
#include <iomanip>
#include <string>
#include "vector.h"
#include "list.h"
#include <list>

int main() {
    List<int> L;
    L.PushFront(3); L.PushFront(2); L.PushFront(1);
    L.PopFront(); L.PopBack();
    L.Display(std::cout);
    L.PopFront();
    L.Display(std::cout);
    L.PushBack(0);
    L.Display(std::cout);
    L.PopBack();
    L.Display(std::cout);
    /*
    ListIterator<int> i;
    i = L.Begin();
    L.Insert(i,0);
    L.Display(std::cout);
    std::cout << L.Size() << '\n';
    i = L.End();
    i = L.Insert(i,4);
    L.Display(std::cout);
    std::cout << L.Size() << '\n';
    --i; --i;
    i = L.Insert(i,6);
    L.Display(std::cout);
    std::cout << L.Size() << '\n';
    i = L.Remove(i);
    L.Display(std::cout);
    std::cout << L.Size() << '\n';
    std::cout << *i << '\n';
    std::cout << "Testing begin and end remove\n";
    i = L.Begin();
    i = L.Remove(i);
    L.Display(std::cout);
    std::cout << L.Size() << '\n';
    std::cout << *i << '\n';
    i = L.End();
    i = L.Remove(i);
    L.Display(std::cout);
    std::cout << L.Size() << '\n';
    std::cout << *(--i) << '\n';
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

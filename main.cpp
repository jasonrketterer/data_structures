#include <iostream>
#include <iomanip>
#include <string>
#include "vector.h"
#include "list.h"
#include <list>

int main() {
    List<int> L;
    L.PushBack(1); L.PushBack(2); L.PushBack(3);
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
    i = L.End(); --i;
    i = L.Remove(i);
    L.Display(std::cout);
    std::cout << L.Size() << '\n';
    std::cout << *(--i) << '\n';

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

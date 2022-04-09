#include <iostream>
#include <iomanip>
#include <string>
#include "vector.h"
#include "list.h"
#include "stack.h"
#include <list>

int main() {
    Stack<int> S;
    S.Push(1); S.Push(2); S.Push(3);
    int val = S.Top();
    S.Display(std::cout);
    S.Pop(); S.Pop(); S.Pop();
    S.Pop();
    val = S.Top();
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

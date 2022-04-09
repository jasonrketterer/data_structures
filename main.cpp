#include <iostream>
#include <iomanip>
#include <string>
#include "vector.h"
#include "list.h"
#include "stack.h"
#include "queue.h"
#include <list>

int main() {
    Queue<int> Q;
    Q.Enqueue(1); Q.Enqueue(2); Q.Enqueue(3);
    Q.Display(std::cout);
    std::cout << Q.Size() << '\n';
    Q.Dequeue();
    Q.Display(std::cout);
    std::cout << Q.Size() << '\n';
    Q.Dequeue(); Q.Dequeue(); Q.Dequeue();
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

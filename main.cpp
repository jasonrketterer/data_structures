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

int main() {
    BST<int> t;
    t.Insert(8); t.Insert(1); t.Insert(12);
    t.Insert(5); t.Insert(0); t.Insert(4);
    t.Insert(6);  t.Insert(10); t.Insert(11);
    t.Insert(9); t.Insert(13);
    t.printVTree();
    std::cout << "\nTree height is " << t.Height() << '\n';
    std::cout << "The number of nodes is " << t.Size() << '\n';
    //t.Remove(8);
    t.Clear();
    std::cout << '\n';
    t.printVTree();
    std::cout << "\nTree height is " << t.Height() << '\n';
    std::cout << "The number of nodes is " << t.Size() << '\n';
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

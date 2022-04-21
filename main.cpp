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
    BST<int> tree;
    tree.Insert(7); tree.Insert(1); tree.Insert(5);
    tree.Insert(8); tree.Insert(0); tree.Insert(4);tree.Insert(6); tree.Insert(9);
    tree.Dump(std::cout, 3, ' ');
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

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
    Graph<int> G{};
    G.readGraphFile();
    G.Dump();
    std::cout << "Vertex" << '\t' << "InDegree" << '\t' << "OutDegree\n";
    for(size_t v = 0; v < G.VertexSize(); ++v) {
        std::cout << std::setw(6) << v << '\t' << std::setw(8) << G.InDegree(v) << '\t'
            << std::setw(8) << G.OutDegree(v) << '\n';
    }
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

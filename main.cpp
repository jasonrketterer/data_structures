#include <iostream>
#include <iomanip>
#include <string>
#include "vector.h"
#include "list.h"

int main() {
    List<int> L;
    L.PushBack(1); L.PushBack(2); L.PushBack(3);
    List<int>::Iterator i = L.Begin();
    L.Insert(i, 4);
    L.Display(std::cout);
    i = L.End();
    L.Insert(i, 5);
    L.Display(std::cout);
    i = L.Begin(); i++; i++;
    L.Insert(i,6);
    L.Display(std::cout);
}

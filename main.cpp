#include <iostream>
#include <iomanip>
#include <string>
#include "vector.h"
#include "list.h"

int main() {
    List<int> L;
    L.PushBack(1); L.PushBack(2); L.PushBack(3);
    for(List<int>::Iterator i = L.Begin(); i != L.End(); ++i)
        std::cout << *i << '\n';
    std::cout << std::endl;
}

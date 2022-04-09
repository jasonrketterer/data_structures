#include <iostream>
#include <iomanip>
#include <string>
#include "vector.h"
#include "list.h"
#include <list>

int main() {
    List<int> L;
    L.PushBack(1); L.PushBack(2); L.PushBack(3);
    L.Dump(std::cout);
    L.Reverse();
    L.Dump(std::cout);
}

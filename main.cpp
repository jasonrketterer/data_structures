#include <iostream>
#include <iomanip>
#include <string>
#include "vector.h"
#include "list.h"

int main() {
    List<int> L;
    L.PushBack(1); L.PushBack(2); L.PushBack(3);
    L.Display(std::cout);
    L.Reverse();
    L.Display(std::cout);
}

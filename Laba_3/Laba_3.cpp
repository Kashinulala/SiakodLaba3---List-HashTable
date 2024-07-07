
#include <iostream>
#include "List.h"


int main()
{
    list A = list();
    A.add(2, 1);
    A.add(4, 1);
    A.add(3, 1);
    A.add(1, 1);
    A.add(5, 1);
    A.listPrint();
    std::cout << "\n";
    A.listPrint();
}
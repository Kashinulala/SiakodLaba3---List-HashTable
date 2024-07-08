
#include <iostream>
#include "List.h"
using namespace std;


int main()
{
    list A = list();
    list B = list();
    list C = list();
    for (int i = 1; i < 5; i+= 1) {
        A.add(i, 6-i);
    }
    for (int i = 1; i < 7; i+= 1) {
        B.add(i, 8-i);
    }

    A.add(10, 1);
    A.print();
    cout << "\n\n";
    cout << A;
    //B.print();
    //cout << "\n\n";
    //cout << B.subset(A);
    //cout << "\n\n";
    //C = B - A;
    //cout << "\n\n";
   // C.print();
}
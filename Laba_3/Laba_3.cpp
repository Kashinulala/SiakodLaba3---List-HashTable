
#include <iostream>
#include "HashTable.h"
using namespace std;


int main()
{
    /*
    cout << A.add(-3, 1);
    cout << A.add(3, 1);
    for (int i = 4; i < 10; i++) {
        cout << A.add(i, 1);
    }

    cout << '\n' << A << '\n';

    cout << A.add(-6, 1);
    cout << A.add(12, 1);
    A + elem(15, 1);

    cout << '\n' << A << '\n';

    cout << A.del(15, 1);
    cout << A.del(-6, 1);
    cout << A.del(12, 1);
    cout << A.del(9, 1);
    cout << A.del(6, 1);

    cout << '\n' << A << '\n';

    cout << A.del(3, 1);

    cout << '\n' << A << '\n';

    cout << A.del(7, 1);

    cout << '\n' << A;
    */
   

    hashTable A = hashTable(3);
    list B = list();
    for (int i = 0; i < 20; i++) {
        B = B + elem(i, 2);
    }

    cout << B << '\n';
    A = A + B;
    hashTable C = hashTable(3);
    cout << A << '\n';
    list D = list();
    for (int i = 0; i < 20; i++) {
        D = D + elem(i, 1);
    }
    C = C + D;
    C - elem(19, 1);
    
    C = C * A;
    cout << C << '\n';

    cout << C << '\n';

    cout << A.getPower() << '\n';
    cout << C.getPower() << '\n';
    C + elem(100, 1);

    cout << A.subset(C);

}
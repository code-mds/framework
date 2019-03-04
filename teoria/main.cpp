#include <iostream>
#include "frazione.h"

using namespace std;

int main()
{
    Frazione f1{3,4};
    Frazione f2{2,5};

    cout << (f1 + f2) << endl;
    cout << "R1=" << (f1 + 5) << endl;
    cout << "R2=" << (5 + f1) << endl; // 5 viene convertito in Frazione

    f1 += 5;
    //5 += f1; non posso farlo, 5 non viene convertito in frazione


    return 0;
}

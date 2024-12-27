#include "Polynom.h"


int main(){
    Polynom p1;
    Monom m1(1.0, 1, new int[1]{2});
    Monom m2(-2.0, 1, new int[1]{1});
    Monom m3(1.0, 1, new int[1]{0});
    Monom m4(1.0, 1, new int[1]{1});
    Monom m5(-1.0, 1, new int[1]{0});

    p1.AppendMonom(m1);
    p1.AppendMonom(m2);
    p1.AppendMonom(m3);
    Polynom p2;
    p2.AppendMonom(m4);
    p2.AppendMonom(m5);   


    Polynom p3;
    p3 = p1/ p2;
    p3.Print();
    cout << endl;
    return 0;
}
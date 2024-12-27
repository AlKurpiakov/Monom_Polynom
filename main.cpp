#include <iostream>
#include "Polynom.h"

void foo1(){
    Polynom p;
    Monom a1 = Monom(4, 1, new int[1]{2});
    Monom a2 = Monom(1, 1, new int[1]{1});
    Monom a3 = Monom(3, 1, new int[1]{0});
    p.AppendMonom(a1);
    p.AppendMonom(a2);
    p.AppendMonom(a3);
    Polynom p1;
    Monom b1 = Monom(2, 1, new int[1]{2});
    Monom b2 = Monom(-1, 1, new int[1]{0});
    p1.AppendMonom(b1);
    p1.AppendMonom(b2);
    Polynom p2 = p / p1;
    p2.Print();
    std::cout << "\n\n";
}

void foo2(){
    Polynom p;
    Monom a1 = Monom(4, 2, new int[2]{2, 2});
    Monom a2 = Monom(1, 2, new int[2]{1, 0});
    Monom a3 = Monom(1, 2, new int[2]{0, 2});
    p.AppendMonom(a1);
    p.AppendMonom(a2);
    p.AppendMonom(a3);
    Polynom p1;
    Monom b1 = Monom(1, 2, new int[2]{2, 0});
    Monom b2 = Monom(1, 2, new int[2]{0, 0});
    p1.AppendMonom(b1);
    p1.AppendMonom(b2);
    Polynom p2 = p / p1;
    p2.Print();
    std::cout << "\n\n";
}

int main(){
    foo1();
    foo2();
    return 0;
}
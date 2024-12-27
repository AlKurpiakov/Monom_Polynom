#include <iostream>
#include "Polynom.h"

int main(){
    Polynom p0;
    Monom a1 = Monom(4, 2, new int16_t[2]{2,3});
    Monom a2 = Monom(1, 1, new int16_t[1]{1});
    Monom a3 = Monom(3, 1, new int16_t[1]{0});
    p0.AppendMonom(a1);
    p0.AppendMonom(a2);
    p0.AppendMonom(a3);
    Polynom p1;
    Monom b1 = Monom(2, 2, new int16_t[2]{1,1});
    Monom b2 = Monom(-1, 1, new int16_t[1]{0});
    p1.AppendMonom(b1);
    p1.AppendMonom(b2);
    Polynom p2 = p0 / p1;
    std::cout<<"res: ";
    p2.Print();
    std::cout << "\n";
    
    return 0;
}

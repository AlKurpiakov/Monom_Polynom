#pragma once
#include "Node.h"

class Polynom {
private:
    Node* _head;
    Monom MaxMonom() const;

public:
    Polynom();
    Polynom(const Polynom& tmp);
    void AppendMonom(Monom monom);
    void DeleteMonom(Node* monom);
    void Print();
    Polynom operator+(const Polynom& polynom) const;
    Polynom operator-(const Polynom& polynom) const;
    Polynom operator*(const Polynom& polynom) const;
    Polynom operator/(const Polynom& polynom) const;



};
#pragma once
#include "Node.h"

class Polynom {
private:
    Node* _head;
    Monom Lead() const;

public:
    Polynom();
    Polynom(const Polynom& tmp);
    void AppendMonom(Monom monom);
    void AppendMonom(double coef, size_t size, int* powers);
    void DeleteMonom(Node* monom);
    void Print();
    string GetLen();
    Polynom operator+(const Polynom& polynom) const;
    Polynom operator-(const Polynom& polynom) const;
    Polynom operator*(const Polynom& polynom) const;
    Polynom operator/(const Polynom& polynom) const;



};
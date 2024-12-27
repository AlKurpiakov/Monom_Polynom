#include "Polynom.h"
#include <cstdint>
#include <cstring>

Polynom::Polynom() {
    _head = nullptr;
}

Polynom::Polynom(const Polynom& tmp) {
    _head = nullptr;
    Node* tmpHead = tmp._head;
    while (tmpHead != nullptr) {
        AppendMonom(tmpHead->GetMonom());
        tmpHead = tmpHead->Next;
    }
}

void Polynom::AppendMonom(Monom monom) {
    if (_head == nullptr) {
        _head = new Node(monom);
    } 
    else 
    {
        Node* tmp = _head;
        while (tmp->Next != nullptr) {
            if (tmp->GetMonom().CanOperate(monom)) {
                Monom result = tmp->GetMonom() + monom;
                if (!result.GetCoef()){
                    DeleteMonom(tmp);
                }
                tmp->SetMonom(result);
                return;
            }
            tmp = tmp->Next;
        }
        if (tmp->GetMonom().CanOperate(monom)) {
                Monom result = tmp->GetMonom() + monom;
                tmp->SetMonom(result);
                return;
        }
        tmp->Next = new Node(monom);
    }
}

void Polynom::Print() {
    Node* tmp = _head;
    while (tmp != nullptr) {
        if (tmp == _head)
            tmp->GetMonom().print();
        else {
            if (tmp->GetMonom().GetCoef() > 0)
                std::cout << "+";
            tmp->GetMonom().print();
        }
        tmp = tmp->Next;
    }
}

Polynom Polynom::operator+(const Polynom& polynom) const {
    Polynom res(*this);
    Node* rightPolynom = polynom._head;

    while (rightPolynom != nullptr)
    {
        res.AppendMonom(rightPolynom->GetMonom());
        rightPolynom = rightPolynom->Next;
    }
    return res;
}

void Polynom::DeleteMonom(Node* monom){
    if (_head == monom){
        Node* temp = _head;
        _head = _head->Next;
        return;
    }

    Node* ref_to_temp = _head;
    Node* temp = _head->Next;
    while (temp->Next != nullptr){
        if (temp == monom){
            ref_to_temp->Next = temp->Next;
            return;
        }
        ref_to_temp = ref_to_temp->Next;
        temp = temp->Next;
    }
    if (temp == monom){
        ref_to_temp->Next = temp->Next;
        return;
    }
}

Polynom Polynom::operator-(const Polynom& polynom) const {
    Polynom res(*this);
    Node* rightPolynom = polynom._head;

    while (rightPolynom != nullptr)
    {
        res.AppendMonom(rightPolynom->GetMonom() * (-1));
        rightPolynom = rightPolynom->Next;
    }
    return res;
}
Polynom Polynom::operator*(const Polynom& polynom) const {
    Polynom res = Polynom();
    Node* LeftPolynom = _head;
    while (LeftPolynom != nullptr){
        Node* RightPolynom = polynom._head;
        while (RightPolynom != nullptr){
            res.AppendMonom(LeftPolynom->GetMonom() * RightPolynom->GetMonom());
            RightPolynom = RightPolynom->Next;
        }
        LeftPolynom = LeftPolynom->Next;
    }
    return res;
}
Polynom Polynom::operator/(const Polynom& polynom) const {
    Polynom res;
    Polynom temp1(*this);
    Polynom temp2;
    Monom m1 = temp1.MaxMonom();
    Monom m2 = polynom.MaxMonom();
    while(m1 >= m2){
        Monom m = m1 / m2;
        res.AppendMonom(m);
        Polynom* temp3 = new Polynom;
        temp3->AppendMonom(m);
        temp2 = *temp3 * polynom;
        temp1 = temp1 - temp2;
        delete temp3;
        m1 = temp1.MaxMonom();
    }
    std::cout<<"Remainder: ";
    temp1.Print();
    std::cout<<"\n";
    return res;
}

Monom Polynom::MaxMonom() const{
    Monom m = _head->GetMonom();
    Node* temp = _head->Next;
    while (temp != nullptr){
        if (temp->GetMonom() >= m){
            m = temp->GetMonom();
        }
        temp = temp->Next;
    }
    return m;
}
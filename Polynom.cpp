#include "Polynom.h"

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

void Polynom::AppendMonom(double coef, size_t size, int* powers){
    
    Node* NewMonom = new Node(coef, size, powers);

    if (_head == nullptr) {
        _head = NewMonom;
    } 
    else 
    {
        Node* tmp = _head;
        while (tmp->Next != nullptr) {
            if (tmp->GetMonom().IsPowerswEquel(Monom(coef, size, powers))) {
                Monom result = tmp->GetMonom() + Monom(coef, size, powers);
                if (!result.GetCoef()){
                    DeleteMonom(tmp);
                }
                tmp->Update(result);
                return;
            }
            tmp = tmp->Next;
        }
        if (tmp->GetMonom().IsPowerswEquel(Monom(coef, size, powers))) {
                Monom result = tmp->GetMonom() + Monom(coef, size, powers);
                tmp->Update(result);
                return;
        }
        tmp->Next = NewMonom;
    }
}

void Polynom::AppendMonom(Monom monom) {
    
    Node* NewMonom = new Node(monom);
    if (_head == nullptr) {
        _head = NewMonom;
    } 
    else 
    {
        Node* tmp = _head;
        while (tmp->Next != nullptr) {
            if (tmp->GetMonom().IsPowerswEquel(monom)) {
                Monom result = tmp->GetMonom() + monom;
                if (!result.GetCoef()){
                    DeleteMonom(tmp);
                }
                tmp->Update(result);
                return;
            }
            tmp = tmp->Next;
        }
        if (tmp->GetMonom().IsPowerswEquel(monom)) {
                Monom result = tmp->GetMonom() + monom;
                tmp->Update(result);
                return;
        }
        tmp->Next = NewMonom;
    }
}



void Polynom::Print() {
    Node* tmp = _head;

    while (tmp != nullptr) {
        if (tmp == _head){
            cout << Monom(tmp->GetMonom()).Mask();
        }
        else {
            cout << "   ";
            cout << Monom(tmp->GetMonom()).Mask();
        }
        tmp = tmp->Next;
    }

    cout << endl;

    Node* tmp2 = _head;
    while (tmp2 != nullptr) {
        if (tmp2 == _head){
            tmp2->GetMonom().Print();
        }
        else {
            if (tmp2->GetMonom().GetCoef() > 0)
                cout << " + ";
            else
                cout << " - ";
            tmp2->GetMonom().Print();
        }
        tmp2 = tmp2->Next;
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
    Monom m1 = temp1.Lead();
    Monom m2 = polynom.Lead();
    while(m1 >= m2){
        Monom m = m1 / m2;
        res.AppendMonom(m);
        Polynom* temp3 = new Polynom;
        temp3->AppendMonom(m);
        temp2 = *temp3 * polynom;
        temp1 = temp1 - temp2;
        delete temp3;
        m1 = temp1.Lead();
    }
    temp1.Print();
    return res;
}

Monom Polynom::Lead() const{
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
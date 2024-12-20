#pragma once
#include "Node.h"

class Polynom{
private:
    Node* _head = nullptr;

public:

    Polynom(){
    }

    void AppendMonom(double coef, size_t size, int* powers){
        Node* NewMonom = new Node(coef, size, powers);
        if (_head == nullptr)   _head = new Node(coef, size, powers);
        else {
            Node* tmp =_head;
            while (tmp->Next != nullptr){
                tmp->UpdateMonom(NewMonom->GetMonom());
                tmp = tmp->Next;
            }
            tmp->Next =  NewMonom;

        }
    }

    void AppendMonom(const Monom& monom){
        Node* NewMonom = new Node(monom);
        if (_head == nullptr)   _head = new Node(monom);
        else {
            Node* tmp =_head;
            while (tmp->Next != nullptr){
                tmp->UpdateMonom(NewMonom->GetMonom());
                tmp = tmp->Next;
            }
            tmp->Next =  NewMonom;

        }
    }

    Polynom(const Polynom& polynom){
        if (polynom._head != nullptr){
            Node* tmpPolynom = polynom._head;
            Node* tmp = _head;
            while (tmpPolynom->Next != nullptr){
                AppendMonom(tmpPolynom->GetMonom());
                tmpPolynom = tmpPolynom->Next;
            }
        }
    }

    Polynom operator+(const Polynom& polynom) const{
        Polynom result(*this);
        Node* tmpPolynom = polynom._head;
        while (tmpPolynom->Next != nullptr) result.AppendMonom(tmpPolynom->GetMonom());
        return result;
    }

    Polynom operator*(const Polynom& polynom) const{
        Polynom result(*this);
        Node* tmpPolynom = polynom._head;
        Node* thisPolynom = _head;
        while (thisPolynom->Next != nullptr)
            while (tmpPolynom->Next != nullptr)
                result.AppendMonom(Monom(thisPolynom->GetMonom() * tmpPolynom->GetMonom()));
            
        return result;
    }



    void Print(){}
};

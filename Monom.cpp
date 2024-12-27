#include "Monom.h"

Monom::Monom(double coef, size_t size, int* powers){
    _coef = coef;
    _size = size;
    _powers = powers;
}

double Monom::GetCoef() const {
    return _coef;
}

void Monom::print() const{
    if (_coef == 0) return;

    
    cout<<_coef;

    for (size_t i = 0; i < _size; i++){
        if (_powers[i] != 0)
        {
            cout<<"x"<<i+1; 
            if (_powers[i] != 1)
                cout<<"^"<<_powers[i];
        }
    }
    cout << " ";
}

Monom::Monom(const Monom& mon){
    _size = mon._size;
    _coef = mon._coef;
    _powers = new int[_size];
    for (size_t i = 0; i < _size; i++){
        _powers[i] = mon._powers[i];
    }
}

Monom& Monom::operator=(const Monom& mon){
    if (this == &mon){
        return *this;
    }
    delete [] _powers;
    _powers = new int[mon._size];
    _size = mon._size;
    _coef = mon._coef;
    for (size_t i = 0; i < _size; i++){
        _powers[i] = mon._powers[i];
    }
    return *this;
}

Monom Monom::operator+(const Monom& mon)const{
    Monom a(*this);
    if (a._size != mon._size){
        throw ;
    }
    for (size_t i = 0; i < _size; i ++){
        if (a._powers[i] != mon._powers[i]){
            throw ;
        }
    }
    a._coef += mon._coef;
    return a;
};

bool Monom::IsPowerswEquel(const Monom& mon) const {
    if (this->_size != mon._size){
        return false;
    }
    for (size_t i = 0; i < _size; i ++){
        if (this->_powers[i] != mon._powers[i]){
            return false;
        }
    }
    return true;
}

bool Monom::operator==(const Monom& m) const{
    return _coef == m.GetCoef() && this->IsPowerswEquel(m);
}

Monom Monom::operator-(const Monom& mon)const{
    Monom a(*this);
    if (a._size != mon._size){
        throw ;
    }
    for (size_t i = 0; i < _size; i ++){
        if (a._powers[i] != mon._powers[i]){
            throw ;
        }
    }
    a._coef -= mon._coef;
    return a;
};

Monom Monom::operator*(const Monom& mon) const{
    size_t mSize = std::max(this->_size, mon._size);
    int* powers = new int[mSize];
    int* maxArr = _powers;
    if (mSize == mon._size)
        maxArr = mon._powers;
    size_t minSize = std::min(this->_size, mon._size);
    for(size_t i = 0; i < mSize; i++){
        powers[i] = i < minSize ? _powers[i] + mon._powers[i] : maxArr[i];
    }
    return Monom(_coef * mon._coef, mSize, powers);
}

Monom Monom::operator/(const Monom& mon) const{
    size_t mSize = std::max(this->_size, mon._size);
    int* powers = new int[mSize];
    size_t minSize = std::min(this->_size, mon._size);
    for(size_t i = 0; i < minSize; i++){
        powers[i] = _powers[i] - mon._powers[i];
    }
    if(this->_size > mon._size){
        for(size_t i = minSize; i < this->_size; i++){
            powers[i] -= _powers[i];
        }
    }
    else{
        for(size_t i = minSize; i < mon._size; i++){
            powers[i] -= mon._powers[i];
        } 
    }
    return Monom(_coef / mon._coef, mSize, powers);
}

Monom Monom::operator*(int number) const{
     return Monom(_coef * -1, _size, _powers);
}

bool Monom::operator>=(const Monom& mon) const{
    for (int i = 0; i < _size; i++){
        if (_powers[i] < mon._powers[i]){
            return false;
        }
    }
    return true;
}

Monom::~Monom(){
    delete [] _powers;
}
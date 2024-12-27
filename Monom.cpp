#include "Monom.h"
#include <iostream>
#include <string>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>

int getlenafpoint(double num) {
    ostringstream oss;
    oss << fixed << std::setprecision(15) << num;
    string s = oss.str();  

    while (!s.empty() && s.back() == '0') {
        s.pop_back();
    }

    if (!s.empty() && s.back() == '.') {
        s.pop_back();
    }

    size_t count_after_decimal;
    size_t pos = s.find('.');

    if (pos == string::npos) 
        count_after_decimal = 0;

    else  
        count_after_decimal = s.size() - pos - 1;
    

    return count_after_decimal;
}


int length(int n) {
    int l = 1;
    for(; n/=10; ++l);
    return l;
}

Monom::Monom(double coef, size_t size, int* powers){
    _coef = coef;
    _size = size;
    _powers = powers;
}

double Monom::GetCoef() const {
    return _coef;
}

string Monom::Mask(){
    string mask;

    int j = _coef;
    double uu;

    int t = length(j);
    while(t-- ) cout << " ";

    double jl;
    uu = modf(_coef, &jl);

    double mm, nn;

    if (uu != 0) cout << " ";

    size_t len = getlenafpoint(_coef);

    while (len--)
        cout << " ";


    for (int i = 0; i < _size; i++){
        int jj = i+1;
        do{
            mask += " ";
            jj /= 10;
        }while(jj / 10 != 0);
        mask += " ";
        mask += to_string(_powers[i]);
    }
    return mask;
}

void Monom::Print() const{
    if (_coef == 0) return;

    
    cout<<abs(_coef);
    int pow;
    for (size_t i = 0; i < _size; i++){
        pow = _powers[i];
        cout<<"x"<<i+1; 
        while(pow % 10 != 0){
            cout << " ";
            pow /= 10;
        }
    }

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
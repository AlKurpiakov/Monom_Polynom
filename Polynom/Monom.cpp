#include "Monom.h"

Monom::Monom(double coef, size_t size, int16_t* array){
    _coef = coef;
    _size = size;
    _array = array;
}

double Monom::GetCoef() const {
    return _coef;
}

void Monom::print() const{
    if (_coef == 0) return;

    std::cout<<_coef;

    for (size_t i = 0; i < _size; i++){
        if (_array[i] != 0)
        {
            std::cout<<"X"<<i+1; 
            if (_array[i] != 1)
                std::cout<<"^"<<_array[i];
        }
    }
}

Monom::Monom(const Monom& mon){
    _size = mon._size;
    _coef = mon._coef;
    _array = new int16_t[_size];
    for (size_t i = 0; i < _size; i++){
        _array[i] = mon._array[i];
    }
}

Monom& Monom::operator=(const Monom& mon){
    if (this == &mon){
        return *this;
    }
    delete [] _array;
    _array = new int16_t[mon._size];
    _size = mon._size;
    _coef = mon._coef;
    for (size_t i = 0; i < _size; i++){
        _array[i] = mon._array[i];
    }
    return *this;
}

bool Monom::CanOperate(const Monom& mon) const {
    if (this->_size != mon._size){
        return false;
    }
    for (size_t i = 0; i < _size; i ++){
        if (this->_array[i] != mon._array[i]){
            return false;
        }
    }
    return true;
}

Monom Monom::operator+(const Monom& mon)const{
    Monom a(*this);
    if(CanOperate(mon)){
        a._coef += mon._coef;
        return a;
    }
    else throw "Incompatible monoms.\n";
};



bool Monom::operator==(const Monom& m) const{
    return _coef == m.GetCoef() && this->CanOperate(m);
}

Monom Monom::operator-(const Monom& mon)const{
    Monom a(*this);
        if(CanOperate(mon)){
            a._coef -= mon._coef;
            return a;
    }
    else throw "Incompatible monoms.\n";
};

Monom Monom::operator*(const Monom& mon) const{
    size_t mSize = std::max(this->_size, mon._size);
    int16_t* array = new int16_t[mSize];
    int16_t* maxArr = _array;
    if (mSize == mon._size)
        maxArr = mon._array;
    size_t minSize = std::min(this->_size, mon._size);
    for(size_t i = 0; i < mSize; i++){
        array[i] = i < minSize ? _array[i] + mon._array[i] : maxArr[i];
    }
    return Monom(_coef * mon._coef, mSize, array);
}

Monom Monom::operator/(const Monom& mon) const{
    size_t mSize = std::max(this->_size, mon._size);
    int16_t* array = new int16_t[mSize];
    size_t minSize = std::min(this->_size, mon._size);
    for(size_t i = 0; i < minSize; i++){
        array[i] = _array[i] - mon._array[i];
    }
    if(this->_size > mon._size){
        for(size_t i = minSize; i < this->_size; i++){
            array[i] -= _array[i];
        } 
    }
    else{
        for(size_t i = minSize; i < mon._size; i++){
            array[i] -= mon._array[i];
        } 
    }
    return Monom(_coef / mon._coef, mSize, array);
}

Monom Monom::operator*(int number) const{
     return Monom(_coef * -1, _size, _array);
}

bool Monom::operator>=(const Monom& mon) const{
    for (int i = 0; i < _size; i++){
        if (_array[i] < mon._array[i]){
            return false;
        }
    }
    return true;
}

Monom::~Monom(){
    delete [] _array;
}
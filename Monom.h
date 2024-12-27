#include <iostream>
#include <cstdint>
using namespace std;


class Monom{
private:
    double _coef;
    size_t _size;
    int* _powers;
public:
    Monom(double coef, size_t size, int* powers);
    double GetCoef() const;
    void print() const;
    Monom(const Monom& mon);
    bool operator==(const Monom& m) const;
    Monom& operator=(const Monom& mon);
    Monom operator+(const Monom& mon)const;
    bool IsPowerswEquel(const Monom& mon) const;
    Monom operator-(const Monom& mon)const;
    Monom operator*(const Monom& mon) const;
    Monom operator*(int number) const;
    Monom operator/(const Monom& mon) const;
    bool operator>=(const Monom& mon) const;
    ~Monom();
};
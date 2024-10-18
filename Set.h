#pragma once
#include "BitField.h"

class Set {
private:
    BitField _bitfield;
    size_t _maxPower;

public:
    Set(size_t maxPower);
    Set(const Set& tmp);
    Set(const BitField& tmp);

    void InsElem(uint64_t elem);
    void DelElem(uint64_t elem);
    bool IsMember(uint64_t elem);
    size_t GetMaxPow() const;

    operator BitField();
    bool operator==(const Set& tmp);
    Set& operator= (const Set& tmp);
    Set operator+(const Set& tmp);
    void operator+(uint64_t elem);
    void operator-(uint64_t elem);
    Set operator*(const Set& elem);
    Set operator~();
    
    friend istream& operator>>(istream& is, Set& tmp);
    friend ostream& operator<<(ostream& is, const Set& tmp);
};
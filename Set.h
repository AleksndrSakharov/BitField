#pragma once
#include "BitField.h"

class Set : BitField
{
private:
    BitField _bitField;
    size_t _maxPower;
public:
    Set(size_t maxPower);
    Set(const Set& tmp);
    Set(const BitField& tmp) : _maxPower(tmp.GetLenght()), _bitField(tmp){
        
    };
    operator BitField(){
        return BitField(this->_bitField);
    };
    void InsElem(uint64_t elem);
    void DelElem(uint64_t elem);
    bool IsMember(uint64_t elem);
    size_t GetMaxPower() const;
    bool operator==(const Set& tmp);
    Set& operator= (const Set& tmp);
    Set operator+(const Set& tmp);
    Set operator+(uint64_t elem);
    Set operator-(uint64_t elem);
    Set operator*(const Set& tmp);
    Set operator~();
    friend istream& operator>>(std::istream& is, Set& tmp);
    friend ostream& operator<<(std::istream& os, const Set& tmp);
};


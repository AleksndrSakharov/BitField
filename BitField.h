#pragma once
#include <iostream>
#include <vector>
#include <stdint.h>
#include <unordered_map>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;


class BitField {
private:
    size_t _memSize;
    size_t _sizeBit;
    uint16_t* _mem;

    size_t GetMemIndex(size_t n)const;
    uint16_t GetMask(size_t n);

public:
    BitField(size_t sizeBit);
    ~BitField();
    BitField(const BitField& tmp);

    void SetBit(size_t n);
    void ClrBit(size_t n);
    uint8_t GetBit(size_t n) ;
    size_t GetLength() const;

    BitField& operator=(const BitField& tmp);
    bool operator==(const BitField& tmp) const;
    BitField operator^(const BitField& tmp);
    BitField operator&(const BitField& tmp);
    BitField operator|(const BitField& tmp);
    BitField operator~();

    BitField Universe();

    friend istream& operator>>(istream& in, BitField& x);
    friend ostream& operator<<(ostream& os, const BitField& x);

};